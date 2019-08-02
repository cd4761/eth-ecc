package ECCPOW_LDPC

//#include "ecc-lib/eccpow.cpp"
import "C"

import (
	"github.com/Onther-Tech/go-ethereum/common"
	"github.com/Onther-Tech/go-ethereum/log"
	"math/big"
	"os"
	"os/user"
	"path/filepath"
	"runtime"
)

var (
	maxUint256  = new(big.Int).Exp(big.NewInt(2), big.NewInt(256), big.NewInt(0))
	sharedLight = new(Light)
)

var DefaultDir = defaultDir()

func defaultDir() string {
	home := os.Getenv("HOME")
	if user, err := user.Current(); err == nil {
		home = user.HomeDir
	}
	if runtime.GOOS == "windows" {
		return filepath.Join(home, "AppData", "EccPoW")
	}
	return filepath.Join(home, ".eccpow")
}

func (l *Light) Verify(block Block) bool {
	// TODO: do ethash_quick_verify before getCache in order
	// to prevent DOS attacks.
	blockNum := block.NumberU64()

	difficulty := block.Difficulty()
	/* Cannot happen if block header diff is validated prior to PoW, but can
		 happen if PoW is checked first due to parallel PoW checking.
		 We could check the minimum valid difficulty but for SoC we avoid (duplicating)
	   Ethereum protocol consensus rules here which are not in scope of Ethash
	*/
	if difficulty.Cmp(common.Big0) == 0 {
		log.Debug("invalid block difficulty")
		return false
	}

	// The actual check.
	target := new(big.Int).Div(maxUint256, difficulty)
	return result.Big().Cmp(target) <= 0
}

func h256ToHash(in C.ethash_h256_t) common.Hash {
	return *(*common.Hash)(unsafe.Pointer(&in.b))
}

func hashToH256(in common.Hash) C.ethash_h256_t {
	return C.ethash_h256_t{b: *(*[32]C.uint8_t)(unsafe.Pointer(&in[0]))}
}

// Full implements the Search half of the proof of work.
type Full struct {
	Dir string // use this to specify a non-default DAG directory

	test     bool // if set use a smaller DAG size
	turbo    bool
	hashRate int32

	mu      sync.Mutex // protects dag
	current *dag       // current full DAG
}

func Search(prev_hash []byte, cur_hash []byte, n uint, wc uint, wr uint) (nonce uint64, mixDigest []byte) {

	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	diff := block.Difficulty()

	i := int64(0)
	starti := i
	start := time.Now().UnixNano()
	previousHashrate := int32(0)

	//nonce = uint64(r.Int63())
	prev_hash := hashToH256(block.PrevHash())
	cur_hash := hashToH256(block.CurHash())
	target := new(big.Int).Div(maxUint256, diff)

	ret := C.compute_ldpc(prev_hash, cur_hash, n, wc, wr)
	//result := h256ToHash(ret.result).Big()
	nonce := uint64(ret.nonce)

	// TODO: disagrees with the spec https://github.comOnther-Tech/wiki/wiki/Ethash#mining
	if ret.success {
		mixDigest = C.GoBytes(unsafe.Pointer(&ret.mix_hash), C.int(32))
		atomic.AddInt32(&pow.hashRate, -previousHashrate)
		return nonce, mixDigest
	}
}

func (pow *Full) GetHashrate() int64 {
	return int64(atomic.LoadInt32(&pow.hashRate))
}

// Ethash combines block verification with Light and
// nonce searching with Full into a single proof of work.
type Ethash struct {
	*Light
	*Full
}

// New creates an instance of the proof of work.
func New() *Ethash {
	return &Ethash{new(Light), &Full{turbo: true}}
}

// NewShared creates an instance of the proof of work., where a single instance
// of the Light cache is shared across all instances created with NewShared.
func NewShared() *Ethash {
	return &Ethash{sharedLight, &Full{turbo: true}}
}

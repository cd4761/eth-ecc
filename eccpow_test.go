package ECCPOW_LDPC

import (
	"math/big"
	"testing"

	"github.com/Onther-Tech/go-ethereum/common"
	"github.com/Onther-Tech/go-ethereum/common/hexutil"
)

//"bytes"
//"encoding/binary"
//"io/ioutil"
//"math/big"
//"os"
//"reflect"
//"sync"
//"testing"
//
//"github.com/Onther-Tech/go-ethereum/common"
//"github.com/Onther-Tech/go-ethereum/common/hexutil"
//"github.com/Onther-Tech/go-ethereum/core/types"

func TestEcc(t *testing.T) {
	prev_hash := hexutil.MustDecode("0xd783efa4d392943503f28438ad5830b2d5964696ffc285f338585e9fe0a37a05")
	cur_hash := hexutil.MustDecode("0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347")
	n = 24
	wc = 3
	wr = 6

	wantDigest := hexutil.MustDecode("0x0000000000000000000000000000000000000000000000000000000000000000")

	nonce, digest := Search(prev_hash, cur_hash, n, wc, wr)
	if !bytes.Equal(digest, wantDigest) {
		t.Errorf("full hashimoto digest mismatch: have %x, want %x", digest, wantDigest)
	}
}

//func init() {
//	// glog.SetV(6)
//	// glog.SetToStderr(true)
//}
//
//type testBlock struct {
//	difficulty  *big.Int
//	hashNoNonce common.Hash
//	nonce       uint64
//	mixDigest   common.Hash
//	number      uint64
//}
//
//func (b *testBlock) Difficulty() *big.Int     { return b.difficulty }
//func (b *testBlock) HashNoNonce() common.Hash { return b.hashNoNonce }
//func (b *testBlock) Nonce() uint64            { return b.nonce }
//func (b *testBlock) MixDigest() common.Hash   { return b.mixDigest }
//func (b *testBlock) NumberU64() uint64        { return b.number }
//
//var validBlocks = []*testBlock{
//	{
//		number:      0,
//		hashNoNonce: common.HexToHash("0000000000000000000000000000000000000000000000000000000000000000"),
//		difficulty:  big.NewInt(0),
//		nonce:       0x0,
//		mixDigest:   common.HexToHash("0000000000000000000000000000000000000000000000000000000000000000"),
//	},
//}
//
//var invalidZeroDiffBlock = testBlock{
//	number:      61440000,
//	hashNoNonce: crypto.Sha3Hash([]byte("foo")),
//	difficulty:  big.NewInt(0),
//	nonce:       0xcafebabec00000fe,
//	mixDigest:   crypto.Sha3Hash([]byte("bar")),
//}

func TestEthashConcurrentVerify(t *testing.T) {
	eth, err := NewForTesting()
	if err != nil {
		t.Fatal(err)
	}

	block := &testBlock{difficulty: big.NewInt(10)}
	nonce, md := eth.Search(block, nil, 0)
	block.nonce = nonce
	block.mixDigest = common.BytesToHash(md)

	// Verify the block concurrently to check for data races.
	//var wg sync.WaitGroup
	//wg.Add(100)
	//for i := 0; i < 100; i++ {
	//	go func() {
	//		if !eth.Verify(block) {
	//			t.Error("Block could not be verified")
	//		}
	//		wg.Done()
	//	}()
	//}
	//wg.Wait()
}

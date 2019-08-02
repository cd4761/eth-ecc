package ECCPOW_LDPC

import (
	"math/big"

	"github.com/Onther-Tech/go-ethereum/common"
)

type Block interface {
	Difficulty() *big.Int
	n() *big.Int
	wc() *big.Int
	wr() *big.Int
	HashNoNonce() common.Hash
	Nonce() uint64
	NumberU64() uint64
	PrevHash() common.Hash
	CurHash() common.Hash
}

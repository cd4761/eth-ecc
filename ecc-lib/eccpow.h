#pragma once

//#ifndef ECCPOW_H
//#define ECCPOW_H

#include "ethash.h"

#define ENABLE_SSE 0

#if defined(_M_X64) && ENABLE_SSE
#include <smmintrin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#define NODE_WORDS (64/4)
//#define MIX_WORDS (ETHASH_MIX_BYTES/4)
//#define MIX_NODES (MIX_WORDS / NODE_WORDS)
//#include <stdint.h>

//typedef union node {
//	uint8_t bytes[NODE_WORDS * 4];
//	uint32_t words[NODE_WORDS];
//	uint64_t double_words[NODE_WORDS / 2];
//
//#if defined(_M_X64) && ENABLE_SSE
//	__m128i xmm[NODE_WORDS/4];
//#endif
//
//} node;

ethash_return_value_t compute_ldpc(char *prev_hash, char *cur_hash, int n, int wc, int wr);

#ifdef __cplusplus
}
#endif



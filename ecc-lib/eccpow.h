#pragma once

#ifndef ECCPOW_H
#define ECCPOW_H

#include "ethash.h"

#ifdef __cplusplus
extern "C" {
#endif

    ethash_return_value_t compute_ldpc(char *prev_hash, char *cur_hash, int n, int wc, int wr);
//int compute_ldpc(char *prev_hash, char *cur_hash, int n, int wc, int wr);

#ifdef __cplusplus
}
#endif

#endif



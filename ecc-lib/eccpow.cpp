// ECCPOW-LDPC.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.


//#include "stdafx.h"
#include "LDPC.h"
#include "ethash.h"
#include <string>
using namespace std;

ethash_return_value_t compute_ldpc(char *prev_hash, char *cur_hash, int n, int wc, int wr)
{
	uint64_t nonce = 0;

	LDPC *ptr = new LDPC;
	ethash_return_value_t ret;

	ptr->set_difficulty(n,wc,wr);				//2 => n = 64, wc = 3, wr = 6,
	if (!ptr->initialization())
	{
		printf("error for calling the initialization function");
		ret.success = false;
		return ret;
	}

	ptr->generate_seed(prev_hash);
	ptr->generate_H();
	ptr->generate_Q();

	while (1)
	{
		string current_block_header_with_nonce;
		current_block_header_with_nonce.assign(cur_hash);
		current_block_header_with_nonce += to_string(nonce);

		ptr->generate_hv((unsigned char*)current_block_header_with_nonce.c_str());
		bool flag = ptr->decision();
		if (!flag) // If a hash vector is a codeword itself, we dont need to run the decoding function.
		{
			ptr->decoding();
			flag = ptr->decision();
		}
		if (flag)
		{
			break;
		}
		nonce++;
	}
	delete ptr;


//	const char zerohash[33] = "00000000000000000000000000000000";
//    ethash_h256_t const* mix_hash = (ethash_h256_t*)zerohash;
//    ret.mix_hash = (ethash_h256_t*)zerohash;
    ret.nonce = nonce;
    ret.success = true;


	return ret;
}


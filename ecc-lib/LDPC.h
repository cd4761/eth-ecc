/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LDPC.h
 * Author: root
 *
 * Created on June 21, 2019, 12:04 AM
 */

#ifndef LDPC_H
#define LDPC_H

#include <cmath>
class LDPC
{
public:

	LDPC();
	~LDPC();

	void set_difficulty(int level);
	bool set_difficulty(int n, int wc, int wr);
	bool initialization();
	bool is_regular(int n, int wc, int wr);

	int  generate_seed(char phv[32]);	//the date type of the previous hash value included in the bitcoin header is the char array of size 32
        int  generate_seed(int seed){ this->seed = seed;};
	bool generate_H();
	bool generate_Q();
	void generate_hv(const unsigned char Seralized_Block_Header_with_Nonce[]);

	void decoding();
	bool decision();

	void print_H(const char name[]);
	void print_Q(const char name[], int type);
	int print_word(const char name[], int type);
	unsigned char *get_hash();



private:
	#define BIG_INFINITY		1000000.0
	#define Inf                     64.0
	int  *hash_vector = NULL;
	int  *output_word = NULL;

	unsigned char tmp_hash_vector[32];	//32bytes => 256bits

	int **H = NULL;
	int **row_in_col = NULL;
	int **col_in_row = NULL;

	int n, m, wc, wr, seed;

	// these parameters are only used for the decoding function.
	int    max_iter = 20;	 // the maximum number of iteration in the decoding function. We fix it.
	double cross_err = 0.01; // a transisient error probability. this is also fixed as a small value.

	double *LRft = NULL;
	double *LRpt = NULL;
	double **LRrtl = NULL;
	double **LRqtl = NULL;

	// these functions are only used for the decoding function.
	double func_f(double x)
	{
		if (x >= BIG_INFINITY)
			return (double)(1.0 / BIG_INFINITY);

		else if (x <= (1.0 / BIG_INFINITY))
			return (double)(BIG_INFINITY);

		else
			return (double)(log((exp(x) + 1) / (exp(x) - 1)));
	}
	double infinity_test(double x)
	{
		if (x >= Inf)
			return Inf;
		else if (x <= -Inf)
			return -Inf;
		else
			return x;
	}
};


#endif /* LDPC_H */


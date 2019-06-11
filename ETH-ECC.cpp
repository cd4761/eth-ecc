#include <Python.h>
#include <alloca.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "LDPC.h"
#include <string>
#include "stdafx.h"

#if PY_MAJOR_VERSION >= 3
#define PY_STRING_FORMAT "y#"
#define PY_CONST_STRING_FORMAT "y"
#else
#define PY_STRING_FORMAT "s#"
#define PY_CONST_STRING_FORMAT "s"
#endif

#define MIX_WORDS (ETHASH_MIX_BYTES/4)

static PyObject *
eth_ecc(PyObject *self, PyObject *args){
  
  char *current_header;
  char *previous_header;
  unsigned long block_number;
  unsigned long long nonce;
  int previous_header_size, current_header_size;

  if (!PyArg_ParseTuple(args, "k" PY_STRING_FORMAT PY_STRING_FORMAT "K", &block_number, &previous_header, &previous_header_size, &current_header, &current_header_size, &nonce))
      return 0;

  if (current_header_size != 32) {
        char error_message[1024];
        sprintf(error_message, "Seed must be 32 bytes long (was %i)", current_header_size);
        PyErr_SetString(PyExc_ValueError, error_message);
        return 0;
  }
  
  unsigned int nonce = 0;

  LDPC *ptr = new LDPC;

	ptr->set_difficulty(24,3,6);				//2 => n = 64, wc = 3, wr = 6, 	
	if (!ptr->initialization())
	{
		printf("error for calling the initialization function");
		return 0;
	}
			
	ptr->generate_seed(&previous_header);
	ptr->generate_H();
	ptr->generate_Q();

  ptr->print_H("H2.txt");
	ptr->print_Q(NULL, 1);
	ptr->print_Q(NULL, 2);

  string current_block_header = &current_header;

  while(1)
  {
    string current_block_header_with_nonce;
		current_block_header_with_nonce.assign(current_block_header);
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
			printf("codeword is founded with nonce = %d\n", nonce);
			break;
		}		
		nonce++;		
  }
  ptr->print_word(NULL, 1);
	ptr->print_word(NULL, 2);
	delete ptr;

	return nonce;
}
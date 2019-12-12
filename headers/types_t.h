#ifndef TYPES_H
	#define TYPES_H
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>
	#include <string.h>
	#include "coord_t.h"
	#include "config_t.h"
	
	#define EMPTY 0
	#define RABBIT 1
	#define FOX 2
	#define ROCK 3
	
	/* Macros for deferencing pointers*/
	#define RABBIT_P(A) ((rabbit_t*)A)
	#define FOX_P(A) ((fox_t*)A)
	
	#define _RED     "\033[1m\033[31m"
	#define _GREEN   "\033[1m\033[32m"
	#define _YELLOW  "\033[1m\033[33m"
	#define _BLUE    "\033[1m\033[34m"
	#define _MAGENTA "\033[1m\033[35m"
	#define _CYAN    "\033[1m\033[36m"
	#define _RESET   "\x1b[0m"

	
	#define NEWANIMAL(GEN_NASCIMENTO, GEN_COMIDA) (animal_t){ \
					  .gen_nascimento = GEN_NASCIMENTO, \
					  .gen_comida = GEN_COMIDA}

	typedef struct animal_t {
		unsigned int gen_nascimento;
		unsigned int gen_comida;
	} animal_t;

	typedef struct object_t {
		unsigned short int type;
		animal_t animal;
		animal_t *candidates;
		int candidates_n;
/*		union {
			fox_t fox;
			rabbit_t rabbit;
		};*/
	} object_t;

	object_t** allocateMatrix (int X, int Y);
	void printMatrix (object_t **eco, int X, int Y, config_t conf);
	int insert_into_matrix (object_t **matrix, char* object_type, coord_t p);
	void deepcopy (object_t** A, object_t** B, int L, int C);

	/*These functions transforms the object into a new_'entity'*/
	void clear_position (object_t *object);




#endif
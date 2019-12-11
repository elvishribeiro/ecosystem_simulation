#ifndef TYPES_H
	#define TYPES_H
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>
	#include <string.h>
	#include "coord_t.h"
	
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


	typedef struct rabbit_t {
		unsigned int age;
	} rabbit_t;

	typedef struct fox_t {
		unsigned int age;
		unsigned int hunger;
	} fox_t;

	typedef struct object_t {
		unsigned short int type; 
		struct object_t *candidates;
		unsigned short int candidates_n;
		void *entity;
	} object_t;

	object_t** allocateMatrix (int X, int Y);
	void printMatrix (object_t **eco, int X, int Y);
	int insert_into_matrix (object_t **matrix, char* object_type, coord_t p);
	void deepcopy (object_t** A, object_t** B, int L, int C);

	/*These functions transforms the object into a new_'entity'*/
	object_t new_rabbit(unsigned int age);
	object_t new_fox(unsigned int age, unsigned int hunger);
	object_t new_rock();
	object_t empty();


#endif
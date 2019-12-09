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
	

	typedef struct rabbit_t {
		unsigned int age;
	} rabbit_t;

	typedef struct fox_t {
		unsigned int age;
		unsigned int hunger;
	} fox_t;

	typedef struct object_t {
		unsigned short int type;
		void *entity;
	} object_t;

	object_t** allocateMatrix (int X, int Y);
	void printMatrix (object_t **eco, int X, int Y);
	int insert_into_matrix (object_t **matrix, char* object_type, coord_t p);

#endif
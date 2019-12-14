#ifndef RULES_H
	#define RULES_H
	#include "types_t.h"
	#include "coord_t.h"
	#include "config_t.h"
	#include <omp.h>

    #define MIN(a, b) ((a) < (b)) ? (a) : (b)
    #define MAX(a, b) ((a) > (b)) ? (a) : (b)

	void rabbit_rules (object_t **eco, config_t conf, coord_t p);
	void fox_rules (object_t **eco, config_t conf, coord_t p);
	void conflict (object_t **eco, config_t conf, int type);

	animal_t choose_rabbit(object_t object);
	animal_t choose_fox(object_t object);

#endif
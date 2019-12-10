#ifndef RULES_H
	#define RULES_H
	#include "types_t.h"
	#include "coord_t.h"
	#include "config_t.h"
	
    #define MIN(a, b) ((a) < (b)) ? (a) : (b)
    #define MAX(a, b) ((a) > (b)) ? (a) : (b)

	void rabbit_rules (object_t **eco, object_t **next_eco, config_t conf, coord_t p);
#endif
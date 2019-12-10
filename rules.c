#include "headers/rules.h"
#include <time.h>

/*find an empty slot*/
coord_t neighbour(object_t **eco, config_t conf, coord_t p, int type) {
	srand(time(NULL));
	coord_t possible[4];
	int possible_n = 0;

	/*up*/
	if (p.x - 1 >= 0 && 
		eco[p.x - 1][p.y].type == type) {
		possible[possible_n++] = (coord_t){.x = p.x - 1, .y = p.y};

	}

	/*right*/
	if (p.y + 1 < conf.C && 
		eco[p.x][p.y + 1].type == type) {
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y + 1};
	}

	/*down*/
	if (p.x + 1 < conf.L && 
		eco[p.x + 1][p.y].type == type) {
		possible[possible_n++] = (coord_t){.x = p.x + 1, .y = p.y};
	}

	/*left*/
	if (p.y - 1 >= 0 && 
		eco[p.x][p.y - 1].type == type) {
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y - 1};
	}

	if (possible_n > 0)
		if (possible_n > 1)
			return possible[(conf.GEN + p.x +p.y) % possible_n];		/*choose one of the neighbours*/
		else
			return possible[0];
	else 
		return (coord_t){.x = -1, .y = -1};
}

/*******************************
--------- Rabbit Rules ---------
********************************/

/* Inserts a rabbit and resolve possible conflicts*/
void rabbit_insert (object_t **eco, object_t **next_eco, rabbit_t r, coord_t p) {
	if (next_eco[p.x][p.y].type == RABBIT) {										/*Conflict: somebody moved here */
		if (RABBIT_P(next_eco[p.x][p.y].entity)->age > r.age)						/*(comparing next_eco instead of eco)*/
			return;
	}
	new_rabbit(&next_eco[p.x][p.y], r.age);
}

/* Make a move if a available slot is found and returns the new position*/
coord_t rabbit_move (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);										
	if (new.x >= 0 && new.y >= 0){
		if (RABBIT_P(next_eco[p.x][p.y].entity)->age >= conf.GEN_PROC_COELHOS) {		/* Reproduction */
			rabbit_insert(eco, next_eco, (rabbit_t){.age = 0}, new);
			new_rabbit(&next_eco[p.x][p.y], 0);
		} else {																/* Move without reproducing */
			rabbit_insert(eco, next_eco, *RABBIT_P(eco[p.x][p.y].entity), new);
			empty(&next_eco[p.x][p.y]);
		}
		return new;
	} 
	return p;										/*No neighbours, returns self position*/
}

void rabbit_rules (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	/* Aging */
	RABBIT_P(eco[p.x][p.y].entity)->age++;
	/* Movement */
	p = rabbit_move (eco, next_eco, conf, p);
}

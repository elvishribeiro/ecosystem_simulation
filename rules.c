#include "headers/rules.h"
#include <time.h>

/*find an slot of type 'type'*/
coord_t neighbour(object_t **eco, config_t conf, coord_t p, int type) {
	srand(time(NULL));
	coord_t possible[4];
	int possible_n = 0;

	/*up*/
	if (p.x - 1 >= 0 && eco[p.x - 1][p.y].type == type)
		possible[possible_n++] = (coord_t){.x = p.x - 1, .y = p.y};

	/*right*/
	if (p.y + 1 < conf.C && eco[p.x][p.y + 1].type == type)
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y + 1};

	/*down*/
	if (p.x + 1 < conf.L && eco[p.x + 1][p.y].type == type)
		possible[possible_n++] = (coord_t){.x = p.x + 1, .y = p.y};

	/*left*/
	if (p.y - 1 >= 0 && eco[p.x][p.y - 1].type == type)
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y - 1};

	if (possible_n > 0){
		if (possible_n > 1)
			return possible[(conf.GEN + p.x +p.y) % possible_n];		/*choose one of the neighbours*/
		else
			return possible[0];
	}
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
	next_eco[p.x][p.y].entity = NULL;
	next_eco[p.x][p.y] = new_rabbit(r.age);
}

/* Make a move if a available slot is found and returns the new position*/
int rabbit_move (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);										
	if (new.x >= 0 && new.y >= 0){
		if (RABBIT_P(next_eco[p.x][p.y].entity)->age >= conf.GEN_PROC_COELHOS) {		/* Reproduction */
			rabbit_insert(eco, next_eco, (rabbit_t){.age = 0}, new);
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = new_rabbit(0);										/*newborns don't age*/
		} 
		else {																/* Move without reproducing */
			rabbit_insert(eco, next_eco, *RABBIT_P(eco[p.x][p.y].entity), new);
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = empty();
			RABBIT_P(next_eco[new.x][new.y].entity)->age++;									/*aging*/
		}
		return 1;
	} 										/*No neighbours, returns false*/
	RABBIT_P(next_eco[p.x][p.y].entity)->age++;	/*aging*/
	return 0;
}

void rabbit_rules (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	/* Movement */
	rabbit_move (eco, next_eco, conf, p);
}


/*******************************
---------- Fox Rules -----------
********************************/


/*Insert the fox f into the next_eco in the position p, resolving conflicts if they ocour*/
void fox_insert (object_t **eco, object_t **next_eco, fox_t f, coord_t p) {
	if (next_eco[p.x][p.y].type == FOX) {										//Conflict: somebody moved here
/*		int candidate_id = next_eco[p.x][p.y].candidates_n++;
		next_eco[p.x][p.y].candidates[candidate_id] = f;*/
		if (FOX_P(next_eco[p.x][p.y].entity)->age > f.age){						//(comparing next_eco instead of eco)
			return;
		}
		else if (FOX_P(next_eco[p.x][p.y].entity)->age < f.age){
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = new_fox(f.age, f.hunger);
			return;
		}
		else {																//ages are equal
			if (FOX_P(next_eco[p.x][p.y].entity)->hunger < f.hunger){		
				return;
			}
			else{
				next_eco[p.x][p.y].entity = NULL;
				next_eco[p.x][p.y] = new_fox(f.age, f.hunger);
				return;
			}
		}
	}
	else {
		next_eco[p.x][p.y].entity = NULL;
		next_eco[p.x][p.y] = new_fox(f.age, f.hunger);
		//int candidate_id = next_eco[p.x][p.y].candidates_n++;
		//next_eco[p.x][p.y].candidates[candidate_id] = f;
		return;
	}
}

int predation(object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, RABBIT);

	if (new.x >= 0 && new.y >= 0){
		if (FOX_P(next_eco[p.x][p.y].entity)->age >= conf.GEN_PROC_RAPOSAS) {		/* Reproduction */
			fox_insert(eco, next_eco, (fox_t){.age = 0, .hunger = 0}, new);
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = new_fox(0, 0);
		} 
		else {																/* Move without reproducing */
			fox_insert(eco, next_eco, *FOX_P(eco[p.x][p.y].entity), new);		
			FOX_P(next_eco[new.x][new.y].entity)->hunger = 0;
			FOX_P(next_eco[new.x][new.y].entity)->age++;
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = empty();
		}
		return 1;
	}
	return 0;
}

/*TODO: fox predation, fox move, fox death*/

int fox_move (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);

	if (new.x >= 0 && new.y >= 0){
		if (FOX_P(next_eco[p.x][p.y].entity)->age >= conf.GEN_PROC_RAPOSAS) {		/* Reproduction */
			fox_insert(eco, next_eco, (fox_t){.age = 0, .hunger = 0}, new);
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = new_fox(0, 0);
		} else {																/* Move without reproducing */
			fox_insert(eco, next_eco, *FOX_P(eco[p.x][p.y].entity), new);
			FOX_P(next_eco[new.x][new.y].entity)->age++;
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = empty();
		}
		return 1;
	}
	return 0;
}

void fox_rules (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	/* Aging */
	//FOX_P(next_eco[p.x][p.y].entity)->hunger++;
	/* Movement */ 
	if (!predation(eco, next_eco, conf, p)) {
		FOX_P(next_eco[p.x][p.y].entity)->hunger++;
		if(FOX_P(eco[p.x][p.y].entity)->hunger >= conf.GEN_COMIDA_RAPOSAS){
			next_eco[p.x][p.y].entity = NULL;
			next_eco[p.x][p.y] = empty();
		}
		else
			fox_move(eco, next_eco, conf, p);
	}
}
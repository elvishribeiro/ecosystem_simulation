#include "headers/rules.h"
#include <time.h>

//find an slot of type 'type'
coord_t neighbour(object_t **eco, config_t conf, coord_t p, int type) {
	srand(time(NULL));
	coord_t possible[4];
	int possible_n = 0;

	//up
	if (p.x - 1 >= 0 && eco[p.x - 1][p.y].type == type)
		possible[possible_n++] = (coord_t){.x = p.x - 1, .y = p.y};

	//right
	if (p.y + 1 < conf.C && eco[p.x][p.y + 1].type == type)
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y + 1};

	//down
	if (p.x + 1 < conf.L && eco[p.x + 1][p.y].type == type)
		possible[possible_n++] = (coord_t){.x = p.x + 1, .y = p.y};

	//left
	if (p.y - 1 >= 0 && eco[p.x][p.y - 1].type == type)
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y - 1};

	if (possible_n > 0){
		if (possible_n > 1)
			return possible[(conf.GEN-1 + p.x +p.y) % possible_n];		//choose one of the neighbours
		else
			return possible[0];
	}
	else 
		return (coord_t){.x = -1, .y = -1};
}

/*******************************
--------- Rabbit Rules ---------
********************************/

// Inserts a rabbit and resolve possible conflicts
void rabbit_insert (object_t **eco, object_t **next_eco, animal_t r, coord_t p) {
	int candidate_id = next_eco[p.x][p.y].candidates_n;

	next_eco[p.x][p.y].type = RABBIT;
	next_eco[p.x][p.y].candidates[candidate_id] = new_animal(r.age, r.hunger, p, r.GEN);
	next_eco[p.x][p.y].candidates_n++;
}

// Make a move if a available slot is found and returns the new position
int rabbit_move (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);										
	if (new.x >= 0 && new.y >= 0){
		if (conf.GEN - eco[p.x][p.y].animal.GEN > conf.GEN_PROC_COELHOS) {		// Reproduction 
			clear_position(&(next_eco[p.x][p.y]));
			clear_position(&(next_eco[new.x][new.y]));
			rabbit_insert(eco, next_eco, new_animal(0, -1, p, conf.GEN), p);
			rabbit_insert(eco, next_eco, new_animal(0, -1, new, conf.GEN), new);
		} 
		else {																// Move without reproducing 
			rabbit_insert(eco, next_eco, eco[p.x][p.y].animal, new);
			clear_position(&(next_eco[p.x][p.y]));
		}
		return 1;
	} 										//No neighbours, returns false
	return 0;
}

void rabbit_rules (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	// Movement 
	rabbit_move (eco, next_eco, conf, p);
	return;
}


/*******************************
---------- Fox Rules -----------
********************************/


/*Insert the fox f into the next_eco in the position p, resolving conflicts if they ocour*/
void fox_insert (object_t **eco, object_t **next_eco, animal_t f, coord_t p) {
	next_eco[p.x][p.y].type = FOX;
	int candidate_id = next_eco[p.x][p.y].candidates_n;
	next_eco[p.x][p.y].candidates[candidate_id] = new_animal(f.age, f.hunger, p, f.GEN);
	next_eco[p.x][p.y].candidates_n++;
}

int predation(object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, RABBIT);

	if (new.x >= 0 && new.y >= 0){
		if (conf.GEN - next_eco[p.x][p.y].animal.GEN > conf.GEN_PROC_RAPOSAS) {		/* Reproduction */
			fox_insert(eco, next_eco, new_animal(0, 0, new, conf.GEN), new);
			next_eco[p.x][p.y].type = FOX;
			next_eco[p.x][p.y].animal = new_animal(0, 0, p, conf.GEN);
		} 
		else {																/* Move without reproducing */
			eco[p.x][p.y].animal.hunger = 0;
			fox_insert(eco, next_eco, eco[p.x][p.y].animal, new);
			clear_position(&(next_eco[p.x][p.y]));
		}
		return 1;
	}
	return 0;
}

/*TODO: fox predation, fox move, fox death*/

int fox_move (object_t **eco, object_t **next_eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);

	if (new.x >= 0 && new.y >= 0){
		if (next_eco[p.x][p.y].animal.age >= conf.GEN_PROC_RAPOSAS) {		/* Reproduction */
			clear_position(&(next_eco[p.x][p.y]));
			clear_position(&(next_eco[new.x][new.y]));
			fox_insert(eco, next_eco, new_animal(0, 0, p, conf.GEN), p);
			fox_insert(eco, next_eco, new_animal(0, 0, new, conf.GEN), new);
		} else {																/* Move without reproducing */
			fox_insert(eco, next_eco, eco[p.x][p.y].animal, new);
			clear_position(&(next_eco[p.x][p.y]));
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
		eco[p.x][p.y].animal.hunger++;
		if(eco[p.x][p.y].animal.hunger >= conf.GEN_COMIDA_RAPOSAS){
			next_eco[p.x][p.y].type = EMPTY;
		}
		else
			fox_move(eco, next_eco, conf, p);
	}
}

animal_t choose_rabbit (object_t object) {
	animal_t *animals = object.candidates;
	int n = object.candidates_n;
	animal_t animal = animals[0];
	for (int i = 0; i < n; i++){
		if (animal.GEN < animals[i].GEN)
			continue;
		else
			animal = animals[i];
	}
	return animal;
}

animal_t choose_fox (object_t object) {
	animal_t *animals = object.candidates;
	int n = object.candidates_n;
	animal_t animal = animals[0];
	for (int i = 0; i < n; i++){
		if (animal.GEN < animals[i].GEN){
			continue;
		}
		else if (animal.GEN > animals[i].GEN){
			animal = animals[i];
		} else {
			if (animal.hunger < animals[i].GEN){
				continue;
			}
			else {
				animal = animals[i];
			}
		}
	}
	return animal;
}

void conflict (object_t **next_eco, config_t conf, int type) {
	if (type == RABBIT) {
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				if (next_eco[i][j].type == RABBIT){
					if (next_eco[i][j].candidates_n == 0)
						continue;
					else {
						next_eco[i][j].animal = choose_rabbit(next_eco[i][j]);
					}
					next_eco[i][j].candidates_n = 0;
				}
			}
		}
	} else if (type == FOX) {
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				if (next_eco[i][j].type == FOX){
					if (next_eco[i][j].candidates_n == 0)
						continue;
					else {
						next_eco[i][j].animal = choose_fox(next_eco[i][j]);
					}
					next_eco[i][j].candidates_n = 0;
				}
			}
		}
	}
}
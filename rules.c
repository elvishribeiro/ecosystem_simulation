#include "headers/rules.h"
#include <time.h>

//find an slot of type 'type'
coord_t neighbour(object_t **eco, config_t conf, coord_t p, int type) {
	srand(time(NULL));
	coord_t possible[4];
	int possible_n = 0;

	//left
	if (p.y - 1 >= 0 && eco[p.x][p.y - 1].animal.type == type)
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y - 1};

	//down
	if (p.x + 1 < conf.L && eco[p.x + 1][p.y].animal.type == type)
		possible[possible_n++] = (coord_t){.x = p.x + 1, .y = p.y};

	//right
	if (p.y + 1 < conf.C && eco[p.x][p.y + 1].animal.type == type)
		possible[possible_n++] = (coord_t){.x = p.x, .y = p.y + 1};

	//up
	if (p.x - 1 >= 0 && eco[p.x - 1][p.y].animal.type == type)
		possible[possible_n++] = (coord_t){.x = p.x - 1, .y = p.y};

	if (possible_n > 0){
		if (possible_n > 1)
			return possible[(conf.GEN + p.x +p.y) % possible_n];		//choose one of the neighbours
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
void rabbit_insert (object_t **eco, animal_t r, coord_t old, coord_t new) {
		int candidate_id;

		if (old.y + 1 == new.y)
			candidate_id = LEFT;
		else if (old.x - 1 == new.x)
			candidate_id = DOWN;
		else if (old.y - 1 == new.y)
			candidate_id = RIGHT;
		else if (old.x + 1 == new.x)
			candidate_id = UP;
		else if (old.x == new.x && old.y == new.y)
			candidate_id = CENTER;

		eco[new.x][new.y].candidates[candidate_id] = r;
}

// Make a move if a available slot is found and returns the new position
int rabbit_move (object_t **eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);										
	if (new.x >= 0 && new.y >= 0){
		if (conf.GEN - eco[p.x][p.y].animal.gen_nascimento > conf.GEN_PROC_COELHOS) {		// Reproduction 
			rabbit_insert(eco, NEWANIMAL(RABBIT, conf.GEN, -1), p, p);			
			rabbit_insert(eco, NEWANIMAL(RABBIT, conf.GEN, -1), p, new);
		} 
		else {																// Move without reproducing 
			rabbit_insert(eco, eco[p.x][p.y].animal, p, new);
		}
		return 1;
	} 										//No neighbours, returns false
	return 0;
}

void rabbit_rules (object_t **eco, config_t conf, coord_t p) {
	// Movement 
	rabbit_move (eco, conf, p);
	return;
}


/*******************************
---------- Fox Rules -----------
********************************/


/*Insert the fox f into the next_eco in the position p, resolving conflicts if they ocour*/
void fox_insert (object_t **eco, animal_t f, coord_t old, coord_t new) {
	int candidate_id;

	if (old.y + 1 == new.y)
		candidate_id = UP;
	else if (old.x - 1 == new.x)
		candidate_id = RIGHT;
	else if (old.y - 1 == new.y)
		candidate_id = DOWN;
	else if (old.x + 1 == new.x)
		candidate_id = LEFT;
	else if (old.x == new.x && old.y == new.y)
		candidate_id = CENTER;

	eco[new.x][new.y].candidates[candidate_id] = f;
}

int predation(object_t **eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, RABBIT);

	if (new.x >= 0 && new.y >= 0){
		if (conf.GEN - eco[p.x][p.y].animal.gen_nascimento > conf.GEN_PROC_RAPOSAS) {		/* Reproduction */
			fox_insert(eco, NEWANIMAL(FOX, conf.GEN, conf.GEN), p, p);
			fox_insert(eco, NEWANIMAL(FOX, conf.GEN, conf.GEN), p, new);
		} 
		else {																/* Move without reproducing */
			fox_insert(eco, NEWANIMAL(FOX, eco[p.x][p.y].animal.gen_nascimento, conf.GEN), p, new);
		}
		return 1;
	}
	return 0;
}

/*TODO: fox predation, fox move, fox death*/

int fox_move (object_t **eco, config_t conf, coord_t p) {
	coord_t new = neighbour(eco, conf, p, EMPTY);

	if (new.x >= 0 && new.y >= 0){
		if (conf.GEN - eco[p.x][p.y].animal.gen_nascimento > conf.GEN_PROC_RAPOSAS) {		/* Reproduction */
			fox_insert(eco, NEWANIMAL(FOX, conf.GEN, conf.GEN), p, p);
			fox_insert(eco, NEWANIMAL(FOX, conf.GEN, conf.GEN), p, new);
		} else {																/* Move without reproducing */
			fox_insert(eco, eco[p.x][p.y].animal, p, new);
		}
		return 1;
	}
	return 0;
}

void fox_rules (object_t **eco, config_t conf, coord_t p) {
	/* Movement */ 
	if (!predation(eco, conf, p)) {
		if(conf.GEN - eco[p.x][p.y].animal.gen_comida >= conf.GEN_COMIDA_RAPOSAS){		//death
			//clear_position(&(next_eco[p.x][p.y]));
		}
		else
			fox_move(eco, conf, p);
	}
}

animal_t choose_rabbit (object_t object) {
	animal_t old_animal = object.animal;

	animal_t *animals = object.candidates;
	animal_t animal;

	int success = 0;
	for (int i = 0; i < 5; i++){
		if (animals[i].type != RABBIT)
			continue;

		success += 1;
		if (success == 1)
			animal = animals[i];

		if (animal.gen_nascimento < animals[i].gen_nascimento)
			continue;
		else
			animal = animals[i];
		animals[i] = NEWANIMAL(EMPTY, -1, -1);

	}
	if (success)
		return animal;
	else if (object.animal.type != RABBIT)
		return old_animal;
	else 
		return NEWANIMAL(EMPTY, -1, -1);
}

animal_t choose_fox (object_t object) {
	animal_t old_animal = object.animal;

	animal_t *animals = object.candidates;
	animal_t animal;

	int success = 0;
	for (int i = 0; i < 5; i++){
		if (animals[i].type != FOX)
			continue;
		
		success += 1;
		if (success == 1)
			animal = animals[i];

		if (animal.gen_nascimento < animals[i].gen_nascimento){
			continue;
		}
		else if (animal.gen_nascimento > animals[i].gen_nascimento){
			animal = animals[i];
		} 
		else {
			if (animal.gen_comida > animals[i].gen_comida){
				continue;
			}
			else {
				animal = animals[i];
			}
		}
		animals[i] = NEWANIMAL(EMPTY, -1, -1);
	}
	if (success)
		return animal;
	else if (object.animal.type != FOX)
		return old_animal;
	else 
		return NEWANIMAL(EMPTY, -1, -1);
}

/*void conflict (object_t **eco, config_t conf, int type) {
	if (type == RABBIT) {
		//#ifdef PARALELO
		#pragma omp parallel for   //paralelo#endif
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				eco[i][j].animal = choose_rabbit(eco[i][j]);
			}
		}
	} 
	else if (type == FOX) {
		//#ifdef PARALELO
		#pragma omp parallel for    //paralelo#endif
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				eco[i][j].animal = choose_fox(eco[i][j]);
			}
		}
	}
}*/
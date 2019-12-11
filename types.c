#include "headers/types_t.h"

object_t **allocateMatrix (int L, int C) {
	object_t **matrix = (object_t**) malloc(L*sizeof(object_t*));
	for (int i = 0; i < L; i++) {
		matrix[i] = (object_t*) calloc(C,sizeof(object_t));
		for (int j = 0; j < C; j++) {
			matrix[i][j].candidates = malloc(4*sizeof(animal_t));
		}
	}
	return matrix;
}


void deepcopy (object_t** A, object_t** B, int L, int C) {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < C; j++) {
			A[i][j] = B[i][j];
		}
	}
}

void printMatrix (object_t **eco, int X, int Y, config_t conf) {
	for (int i = 0; i < X; i++){
		printf("|");
		for (int j = 0; j < Y; j++) {
			if (eco[i][j].type == EMPTY)
				printf("   ");
			else if (eco[i][j].type == ROCK)
				printf(" * ");
			else if (eco[i][j].type == RABBIT)
				printf(_GREEN"R%d "_RESET, conf.GEN - eco[i][j].animal.GEN);
			else if (eco[i][j].type == FOX)
				printf(_RED"F%d%d"_RESET, conf.GEN - eco[i][j].animal.GEN, eco[i][j].animal.hunger);
			else
				printf("?");
			printf("|");
		}
		printf("\n");
	}
	printf("---------------------\n");
}

int insert_into_matrix (object_t **matrix, char* object_type, coord_t p) {
	if (strcmp(object_type, "COELHO") == 0) {
		matrix[p.x][p.y].type = RABBIT;
		matrix[p.x][p.y].animal = new_animal(0, -1, p, 0);

	}
	else if (strcmp(object_type, "RAPOSA") == 0) {
		matrix[p.x][p.y].type = FOX;
		matrix[p.x][p.y].animal = new_animal(0, 0, p, 0);
	}
	else if (strcmp(object_type, "ROCHA") == 0) {
		matrix[p.x][p.y].type = ROCK;
	}
	else
		matrix[p.x][p.y].type = EMPTY;

	return 1;
}

object_t new_rabbit (unsigned int age) {
	object_t object;
	object.type = RABBIT;
	object.animal.age = age;
	return object;
}

object_t new_fox (unsigned int age, unsigned int hunger) {
	object_t object;
	object.type = FOX;
	object.animal.age = age;
	object.animal.hunger = hunger;
	return object;
}

object_t new_rock () {
	object_t object;
	object.type = ROCK;
	return object;
}

object_t empty () {
	object_t object;
	object.type = EMPTY;
	//if (object.entity != NULL) free(object.entity);
	return object;
}

animal_t new_animal (unsigned int age, unsigned int hunger, coord_t p, unsigned int GEN) {
	return (animal_t){.age = age, .hunger = hunger, .p = p, .GEN = GEN};
}

void clear_position (object_t *object) {
	object->type = EMPTY;
	object->animal = new_animal(-1,-1,(coord_t){.x = -1, .y = -1},-1);
	object->candidates_n = 0;
}
#include "headers/types_t.h"

object_t **allocateMatrix (int L, int C) {
	object_t **matrix = (object_t**) malloc(L*sizeof(object_t*));
	for (int i = 0; i < L; i++) {
		matrix[i] = (object_t*) malloc(C*sizeof(object_t));
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

void printMatrix (object_t **eco, int X, int Y) {
	for (int i = 0; i < X; i++){
		printf("|");
		for (int j = 0; j < Y; j++) {
			if (eco[i][j].type == EMPTY)
				printf("   ");
			else if (eco[i][j].type == ROCK)
				printf(" * ");
			else if (eco[i][j].type == RABBIT)
				printf(_GREEN"R%d "_RESET, RABBIT_P(eco[i][j].entity)->age);
			else if (eco[i][j].type == FOX)
				printf(_RED"F%d%d"_RESET, FOX_P(eco[i][j].entity)->age, FOX_P(eco[i][j].entity)->hunger);
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
		matrix[p.x][p.y] = new_rabbit(0);
	}
	else if (strcmp(object_type, "RAPOSA") == 0) {
		matrix[p.x][p.y] = new_fox(0, 0);
	}
	else if (strcmp(object_type, "ROCHA") == 0) {
		matrix[p.x][p.y] = new_rock();
	}

	return 1;
}

object_t new_rabbit (unsigned int age) {
	object_t object;
	object.type = RABBIT;
	object.entity = (rabbit_t*) malloc(sizeof(rabbit_t));
	RABBIT_P(object.entity)->age = age;
	return object;
}

object_t new_fox (unsigned int age, unsigned int hunger) {
	object_t object;
	object.type = FOX;
	object.entity = (fox_t*) malloc(sizeof(fox_t));
	FOX_P(object.entity)->age = age;
	FOX_P(object.entity)->hunger = hunger;
	return object;
}

object_t new_rock () {
	object_t object;
	object.type = ROCK;
	object.entity = NULL;
	return object;
}

object_t empty () {
	object_t object;
	object.type = EMPTY;
	//if (object.entity != NULL) free(object.entity);
	object.entity = NULL;
	return object;
}
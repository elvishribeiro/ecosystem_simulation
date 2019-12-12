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
				printf(_GREEN"R%-2d"_RESET, conf.GEN - eco[i][j].animal.gen_nascimento);
			else if (eco[i][j].type == FOX)
				printf(_RED"F%d%d"_RESET, conf.GEN - eco[i][j].animal.gen_nascimento, conf.GEN - eco[i][j].animal.gen_comida);
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
		matrix[p.x][p.y].animal = NEWANIMAL(0, -1);

	}
	else if (strcmp(object_type, "RAPOSA") == 0) {
		matrix[p.x][p.y].type = FOX;
		matrix[p.x][p.y].animal = NEWANIMAL(0, 0);
	}
	else if (strcmp(object_type, "ROCHA") == 0) {
		matrix[p.x][p.y].type = ROCK;
	}
	else
		matrix[p.x][p.y].type = EMPTY;

	return 1;
}

void clear_position (object_t *object) {
	object->type = EMPTY;
	object->animal = NEWANIMAL(-1, -1);
	object->candidates_n = 0;
}
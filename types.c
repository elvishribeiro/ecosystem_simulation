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
		for (int j = 0; j < Y; j++) {
			if (eco[i][j].type == EMPTY)
				printf(" ");
			else if (eco[i][j].type == ROCK)
				printf("*");
			else if (eco[i][j].type == RABBIT)
				printf("R");
			else if (eco[i][j].type == FOX)
				printf("F");
			else
				printf("?");
		}
		printf("\n");
	}
}

int insert_into_matrix (object_t **matrix, char* object_type, coord_t p) {
	if (strcmp(object_type, "COELHO") == 0) {
		matrix[p.x][p.y].type = RABBIT;
		matrix[p.x][p.y].entity = (rabbit_t*) malloc (sizeof(rabbit_t));

	}
	else if (strcmp(object_type, "RAPOSA") == 0) {
		matrix[p.x][p.y].type = FOX;
		matrix[p.x][p.y].entity = (fox_t*) malloc (sizeof(fox_t));
	}
	else if (strcmp(object_type, "ROCHA") == 0) {
		matrix[p.x][p.y].type = ROCK;
		matrix[p.x][p.y].entity = NULL;
	}

	return 1;
}

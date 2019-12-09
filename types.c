#include "headers/types_t.h"

object_t** allocateMatrix (int X, int Y) {
	object_t **c;

	c = (object_t**) malloc (X * sizeof(object_t*));
	
	if (c == NULL){
		perror("");
		exit(1);
	}

	for (int i = 0; i < X; ++i) {
		c[i] = (object_t*) calloc (Y, sizeof(object_t));
		if (c[i] == NULL){
			perror("");
			exit(1);
		}
	}
	return c;
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

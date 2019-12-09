#include "headers/types_t.h"

object_t **allocateMatrix (int L, int C) {
    object_t **matrix = malloc(L * sizeof(object_t*));
    matrix[0] = malloc(L * C * sizeof(object_t));

    if (matrix == NULL){
        perror("Error in function allocateMatrix: ");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < C; i++) 
        matrix[i] = matrix[i-1] + L;

    return matrix;
}

void freeMatrix (object_t** matrix){
    free(matrix[0]);
    free(matrix);
}

void printMatrix (object_t **eco, int X, int Y) {
	for (int i = 0; i < X; i++){
		for (int j = 0; j < Y; j++) {
			printf("%p ", &(eco[i][j]));
			/*if (eco[i][j].type == EMPTY)
				printf(" ");
			else if (eco[i][j].type == ROCK)
				printf("*");
			else if (eco[i][j].type == RABBIT)
				printf("R");
			else if (eco[i][j].type == FOX)
				printf("F");
			else
				printf("?");*/
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

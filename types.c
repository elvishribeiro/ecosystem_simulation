#include "headers/types_t.h"

object_t **allocateMatrix (int L, int C) {
	object_t **matrix = (object_t**) malloc(L*sizeof(object_t*));
	for (int i = 0; i < L; i++) {
		matrix[i] = (object_t*) calloc(C,sizeof(object_t));
		for (int j = 0; j < C; j++) {
			matrix[i][j].candidates = malloc(5*sizeof(animal_t));
		}
	}
	return matrix;
}

void printMatrix (object_t **eco, int X, int Y, config_t conf) {
	for (int i = 0; i < X; i++){
		printf("|");
		for (int j = 0; j < Y; j++) {
			if (eco[i][j].animal.type == EMPTY)
				printf("   ");
			else if (eco[i][j].animal.type == ROCK)
				printf(" * ");
			else if (eco[i][j].animal.type == RABBIT)
				printf(_GREEN"R%-2d"_RESET, conf.GEN - eco[i][j].animal.gen_nascimento);
			else if (eco[i][j].animal.type == FOX)
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
		matrix[p.x][p.y].animal = NEWANIMAL(RABBIT, 0, -1);
	}
	else if (strcmp(object_type, "RAPOSA") == 0) {
		matrix[p.x][p.y].animal = NEWANIMAL(FOX, 0, 0);
	}
	else if (strcmp(object_type, "ROCHA") == 0) {
		matrix[p.x][p.y].animal = NEWANIMAL(ROCK, -1, -1);
	}
	else
		matrix[p.x][p.y].animal = NEWANIMAL(EMPTY, -1, -1);
	return 1;
}

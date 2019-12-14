#include "headers/fileHandler.h"


/*Reads the file passed by the string filename returning a configuration struct and the ecosystem matrix*/
int readFile (char *filename, config_t *conf, object_t ***eco) {
	FILE *fp;
	unsigned int N;
	char object_type[7];
	coord_t p;
	object_t  **matrix;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror(filename);
		exit(1);
	}

	/*TODO -- file checking*/
	fscanf(fp, "%hu %hu %hu %u %u %u %u\n",&(conf->GEN_PROC_COELHOS),
										&(conf->GEN_PROC_RAPOSAS),
										&(conf->GEN_COMIDA_RAPOSAS),
										&(conf->N_GEN),
										&(conf->L),
										&(conf->C),
										&N);
	conf->GEN = 0;
	
	matrix = allocateMatrix(conf->L, conf->C);

	for (int i = 0; i < N; i++) {
		fscanf(fp, "%s %d %d\n", object_type, &(p.x), &(p.y));
		insert_into_matrix(matrix, object_type, p);
	}

	*eco = matrix;
	
	return 1;
}
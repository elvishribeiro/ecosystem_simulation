#include "headers/fileHandler.h"

int readFile (char *filename, config_t *c) {
	FILE *fp;
	unsigned int N;
	char object[7];
	coord_t p;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror(filename);
		exit(1);
	}

	fscanf(fp, "%u %u %u %u %u %u %u\n",&(c->GEN_PROC_COELHOS),
										&(c->GEN_PROC_RAPOSAS),
										&(c->GEN_COMIDA_RAPOSAS),
										&(c->N_GEN),
										&(c->L),
										&(c->C),
										&N);

	for (int i = 0; i < N; i++) {
		fscanf(fp, "%s %d %d\n", object, &(p.x), &(p.y));
	}

	return 1;
}
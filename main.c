#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers/fileHandler.h"
#include "headers/config_t.h"
#include "headers/types_t.h"
#include "headers/rules.h"
#include "headers/coord_t.h"

int main (int argc, char **argv) {
	if (argc < 2) {
		printf("Usage:\n%s <config_file>\n\n", argv[0]);
		exit(1);
	}

	config_t conf;

	object_t **eco, **next_eco;
	coord_t p;

	
	readFile(argv[1], &conf, &eco);

	int matrix_size = conf.L*conf.C*sizeof(object_t);

	next_eco = allocateMatrix(conf.L, conf.C);
	deepcopy(next_eco, eco, conf.L, conf.C);

	system("clear");
	printf("-------GEN:%2d-------\n", 0);
	printMatrix (eco, conf.L, conf.C, conf);

	//usleep(500000);
	getchar();
	system("clear");
	printf("-------GEN:%2d-------\n", 1);

	for (unsigned int t = 1; t <= conf.N_GEN; t++){
		conf.GEN++;
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				p = (coord_t){.x = i, .y = j};
				if (eco[i][j].type == RABBIT){
					rabbit_rules (eco, next_eco, conf, p);
				}	
			}
		}
		conflict(next_eco, conf, RABBIT);
		deepcopy(eco, next_eco, conf.L, conf.C);
		printMatrix (eco, conf.L, conf.C, conf);
		//usleep(500000);
		getchar();
		system("clear");
		printf("-------GEN:%2d-------\n", t);
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				p = (coord_t){.x = i, .y = j};
				if (eco[i][j].type == FOX){
					fox_rules (eco, next_eco, conf, p);
				}	
			}
		}
		conflict(next_eco, conf, FOX);
		deepcopy(eco, next_eco, conf.L, conf.C);

		printMatrix (eco, conf.L, conf.C, conf);
		//usleep(500000);
		getchar();
		system("clear");
		printf("-------GEN:%2d-------\n", t+1);
	}

	printMatrix (eco, conf.L, conf.C, conf);

	return 0;
}
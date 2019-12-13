#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers/fileHandler.h"
#include "headers/config_t.h"
#include "headers/types_t.h"
#include "headers/rules.h"
#include "headers/coord_t.h"

void printResult (object_t **eco, config_t conf) {
	int N = 0;
	for (unsigned int i = 0; i < conf.L; i++)
		for (unsigned int j = 0; j < conf.C; j++)
			if (eco[i][j].type != EMPTY)
				N++;

	printf("%u %u %u 0 %u %u %u\n",conf.GEN_PROC_COELHOS,
									conf.GEN_PROC_RAPOSAS,
									conf.GEN_COMIDA_RAPOSAS,
									conf.L,
									conf.C,
									N);
	for (unsigned int i = 0; i < conf.L; i++)
		for (unsigned int j = 0; j < conf.C; j++)
			if (eco[i][j].type != EMPTY){
				if (eco[i][j].type == FOX) {
					printf("RAPOSA %d %d\n", i, j);
				}
				else if (eco[i][j].type == RABBIT) {
					printf("COELHO %d %d\n", i, j);
				}
				else if (eco[i][j].type == ROCK) {
					printf("ROCHA %d %d\n", i, j);
				}
			}
}

int main (int argc, char **argv) {
	if (argc < 2) {
		printf("Usage:\n%s <config_file>\n\n", argv[0]);
		exit(1);
	}

	config_t conf;

	object_t **eco, **next_eco;
	coord_t p;

	
	readFile(argv[1], &conf, &eco);
	//readFile("mx/m30.txt", &conf, &eco);
	next_eco = allocateMatrix(conf.L, conf.C);
	deepcopy(next_eco, eco, conf.L, conf.C);

	#ifdef STEP
		system("clear");
		printf("-------GEN:%2d-------\n", 0);
		printMatrix (eco, conf.L, conf.C, conf);
		
		getchar();
		system("clear");
		printf("-------GEN:%2d-------\n", 1);
	#endif

	for (unsigned int t = 1; t <= conf.N_GEN; t++){
		conf.GEN++;
		// COELHO
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				if (eco[i][j].type == RABBIT){
					p = (coord_t){.x = i, .y = j};
					rabbit_rules (eco, next_eco, conf, p);
				}	
			}
		}
		conflict(next_eco, conf, RABBIT);
		deepcopy(eco, next_eco, conf.L, conf.C);

/*		#ifdef STEP
			printMatrix (eco, conf.L, conf.C, conf);
			getchar();
			system("clear");
			printf("-------GEN:%2d-------\n", t);
		#endif*/
		for (unsigned int i = 0; i < conf.L; i++){
			for (unsigned int j = 0; j < conf.C; j++){
				if (eco[i][j].type == FOX){
					p = (coord_t){.x = i, .y = j};
					fox_rules (eco, next_eco, conf, p);
				}	
			}
		}
		conflict(next_eco, conf, FOX);
		deepcopy(eco, next_eco, conf.L, conf.C);

		#ifdef STEP
			printMatrix (eco, conf.L, conf.C, conf);
			getchar();
			system("clear");
			printf("-------GEN:%2d-------\n", t+1);
		#endif
	}

	#ifdef STEP
		printf("-------GEN:%2d-------\n", conf.GEN);
		printMatrix (eco, conf.L, conf.C, conf);
	#endif

	printResult(eco, conf);
	return 0;
}
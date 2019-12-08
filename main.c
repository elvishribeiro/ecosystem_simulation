#include <stdio.h>
#include <stdlib.h>
#include "headers/fileHandler.h"
#include "headers/config_t.h"

int main (int argc, char **argv) {

	if (argc < 2) {
		printf("Usage:\n%s <config_file>\n\n", argv[0]);
		exit(1);
	}

	config_t conf;
	readFile(argv[1], &conf);

	return 0;
}
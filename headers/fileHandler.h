/*Functions to handle interactions with files*/

#ifndef FILEHANDLER_H
	#define FILEHANDLER_H

	#include "config_t.h"
	#include "coord_t.h"
	#include "types_t.h"
	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>
	#include <string.h>

	int readFile (char *filename, config_t *c, object_t ***eco);
#endif
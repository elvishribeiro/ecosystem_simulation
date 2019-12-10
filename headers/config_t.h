/*Struct with the configuration passed by the file*/
#ifndef CONFIG_H
	#define CONFIG_H
	typedef struct config_t {
		unsigned short int GEN_PROC_COELHOS;
		unsigned short int GEN_PROC_RAPOSAS;
		unsigned short int GEN_COMIDA_RAPOSAS;
		unsigned int N_GEN;
		unsigned int L;
		unsigned int C;
	} config_t;
#endif

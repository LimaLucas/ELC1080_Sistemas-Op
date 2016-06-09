#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char** argv){
	if(!testInput(argc, argv))
		return -1;

	return 0;
}

int testInput(int argc, char **argv){
	if(argc!=2){
		printf("Informe o número de consumidores!\n");
		return 0;
	}else{
		sscanf(argv[1], "%i", &gQtde);
		
		if(gQtde<1){ 
			printf("Deve haver pelo menos 1 consumidor!\n");
			return 0;
		}
	}
	return 1;
}
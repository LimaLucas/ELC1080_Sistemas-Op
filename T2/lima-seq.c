#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 1000000
#define MIN 1

// Variável global para armazenar o valor buscado
int gX = 0;

// Função de busca
int funcao();

// Função que calcula a diferença entre tempo inicial e final
double difTime(struct timespec t0, struct timespec t1);

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char** argv){
	struct timespec t0, t1;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

	if(!testInput(argc, argv))
		return -1;

	printf("Valor buscado: \t%i\nQtd de threads: 0\n", gX);
	
	int i = funcao();

	clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
	printf("Tempo de execução:\t\t%lf seg.\n", difTime(t0, t1));

	return 0;
}

int funcao(){
	int i;
	for(i=MIN; i<=MAX; i++) // Percorre todo o periodo
		if(gX==i){
			printf("Algoritmo sequencial\t1\n");
		}
	return 1;
}

double difTime(struct timespec t0, struct timespec t1){
    return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int testInput(int argc, char **argv){
	if(argc!=2){
		printf("Informe o num. buscado !\n");
		return 0;
	}else{
		gX = atoi(argv[1]);

		if(gX<MIN || gX>MAX){ 
			printf("O valor buscado deve estar entre 0 e 1mi!\n");
			return 0;
		}
	}
	return 1;
}
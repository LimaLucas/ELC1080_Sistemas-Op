#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 1000000
#define MIN 0

// Variáveis globais para armazenar o valor buscado e número de threads
int gX = 0;
int gT = 0;

// Função da Thread
void * funcThread(void * index);

// Função que calcula a diferença entre tempo inicial e final
double difTime(struct timespec t0, struct timespec t1);

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char **argv){
	//INICIALIZAÇÃO
	struct timespec t0, t1, t2, t3;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

	if(!testInput(argc, argv))
		return -1;
	int i;

	printf("Valor buscado: \t%i\nQtde de threads: %i\n\n\tID\tEncontrou\n", gX, gT);

	// CRIAÇÃO DAS THREADS
	clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
	pthread_t lThread[gT]; // Cria lista de threads de tamanho gT informado por parâmetro

	for(i=0; i<gT; i++){
		pthread_create(&lThread[i], NULL, funcThread, (void *) i);
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

	// JUNÇÃO DAS THREADS
	for(i=0; i<gT; i++)
		pthread_join(lThread[i], NULL);

	clock_gettime(CLOCK_MONOTONIC_RAW, &t3);
	
	// FINALIZAÇÃO
	printf("\nTempo de criação das threads:\t%lf seg.\n", difTime(t1, t2));
	printf("Tempo de junção das threads:\t%lf seg.\n", difTime(t2, t3));
	printf("Tempo de execução:\t\t%lf seg.\n", difTime(t0, t3));

	return 0;
}

void * funcThread(void * index){
	int i;
	int id = (int) index;
	int ini = (MAX/gT)*id;  // Especifica o inicio do periodo a ser verificado
	int fin = ini+(MAX/gT); // Especifica o final do periodo

	for(i=ini; i<fin; i++) // Percorre todo o periodo referente a uma thread
		if(gX==i){
			printf("Thread\t%i \t1\n", id);
			pthread_exit(NULL);
		}

	if(id==gT-1 && gX == MAX){ // Condição para que a última thread também verifique o valor MAX
		printf("Thread\t%i \t0\n", id);
		pthread_exit(NULL);
	}

	printf("Thread\t%i \t0\n", id);
	pthread_exit(NULL);
}

double difTime(struct timespec t0, struct timespec t1){
    return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int testInput(int argc, char **argv){
	if(argc!=3){
		printf("Informe o num. buscado e a qtde de threads!\n");
		return 0;
	}else{
		gX = atoi(argv[1]);
		gT = atoi(argv[2]);

		if(gX<MIN || gX>MAX){ 
			printf("O valor buscado deve estar entre 0 e 1mi!\n");
			return 0;
		}else if(gT!=1 && gT!=2 && gT!=5 && gT!=10 && gT!=20){
			printf("A quantidade de threads deve 1, 2, 5, 10 ou 20!\n");
			return 0;
		}
	}
	return 1;
}
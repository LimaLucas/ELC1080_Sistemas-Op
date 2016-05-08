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

// Função que calcula a diferença entre um tempo inicial e um final
double difTime(struct timespec t0, struct timespec t1);

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char **argv){
	//INICIALIZAÇÃO
	struct timespec tE0, tE1, tC0, tC1, tJ0, tJ1;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tE0); //Tempo inicial de execução

	if(!testInput(argc, argv))
		return -1;
	int i;

	printf("Valor buscado: \t%i\nQtde de threads: \t%i\n\n\tID\tEncontrou\n", gX, gT);

	// CRIAÇÃO DAS THREADS
	clock_gettime(CLOCK_MONOTONIC_RAW, &tC0); //Tempo inicial da criação
	pthread_t lThread[gT]; // Cria lista de threads de tamanho gT informado por parâmetro

	for(i=0; i<gT; i++){
		pthread_create(&lThread[i], NULL, funcThread, (void *) i);
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &tC1); //Tempo final da criação

	// JUNÇÃO DAS THREADS
	clock_gettime(CLOCK_MONOTONIC_RAW, &tJ0); //Tempo inicial da junção

	for(i=0; i<gT; i++){
		pthread_join(lThread[i], NULL);
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &tJ1); //Tempo final da junção
	
	// FINALIZAÇÃO
	clock_gettime(CLOCK_MONOTONIC_RAW, &tE1); //Tempo final de execução
	
	printf("\nTempo de criação das threads:\t%lf seg.\n", difTime(tC0, tC1));
	printf("Tempo de junção das threads:\t%lf seg.\n", difTime(tJ0, tJ1));
	printf("Tempo de execução:\t%lf seg.\n", difTime(tE0, tE1));

	return 0;
}

void * funcThread(void * index){
	int i, flag = 0;
	int id = (int) index;
	int ini = (MAX/gT)*id;  // Especifica o inicio do periodo a ser verificado
	int fin = ini+(MAX/gT); // Especifica o final

	for(i=ini; i<fin; i++)
		if(gX==i)
			flag = 1;

	if(id==gT-1 && gX == MAX) // Condição para que a última thread também verifique valor MAX
		flag = 1;

	if(flag == 1)
		printf("Thread\t%i \t1\n", id);
	else
		printf("Thread\t%i \t0\n", id);
}

double difTime(struct timespec t0, struct timespec t1){
    return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int testInput(int argc, char **argv){
	if(argc<3){ // Verifica a entrada de 3 valores, alg. X e T
		printf("Informe o num. buscado e a qtde de threads!\n");
		return 0;
	}else{
		gX = atoi(argv[1]);
		gT = atoi(argv[2]);

		if(gX<MIN || gX>MAX){ // Varifica de valor a ser buscado está dentro do periodo especificado
			printf("O valor buscado deve estar entre 0 e 1mi!\n");
			return 0;
		}else if(gT!=1 && gT!=2 && gT!=5 && gT!=10 && gT!=20){ // Verifica se a qtde de threads é valida
			printf("A quantidade de threads deve 1, 2, 5, 10 ou 20!\n");
			return 0;
		}
	}
	return 1;
}
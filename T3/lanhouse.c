#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define PCS 3 	// Qtde de PCs disponívels
#define MAX 15	// Qtde máxima de clientes em espera

// Variável global para armazenar a qtde de clientes
int gQtde = 0;

// Lista FIFO de cliente na em espera na lanhouse
typedef struct client{
	int id;
	pthread_t thread;
} Client;

// Estrutura do semáforo
typedef struct pc{
	int id;
	pthread_t thread;
} PC;

// Thread para utilização de cada PC
void* threadPC(void* index);

// Thread para chegada de cada cliente
void* threadClient(void* index);

// Função que calcula a diferença entre tempo inicial e final
double difTime(struct timespec t0, struct timespec t1);

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char** argv){
	if(!testInput(argc, argv))
		return -1;

	int i;
	pthread_t tPC[PCS]; 		// Cria lista de threads de PCS
	pthread_t tClient[gQtde];	// Cria lista de threads de Clientes

	// Criação das threads Clientes e thrads PCs
	for(i=0; i<PCS; i++)
		pthread_create(&tPC[i].thread, NULL, threadPC, (void*)i);
	for(i=0; i<gQtde; i++)
		pthread_create(&tClient[i].thread, NULL, threadClient, (void*)i);

	// Junção das threads PCs e thrads Clientes
	for(i=0; i<gQtde; i++)
		pthread_join(tClient[i].thread, NULL);
	for(i=0; i<PCS; i++)
		pthread_join(tPC[i].thread, NULL);

	return 0;
}

void* threadPC(void* index){

}

void* threadClient(void* index){

}

double difTime(struct timespec t0, struct timespec t1){
    return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int testInput(int argc, char **argv){
	if(argc!=2){
		printf("Informe a quantidade de clientes!\n");
		return 0;
	}else{
		sscanf(argv[1], "%i", &gQtde);
		
		if(gQtde<1){ 
			printf("Deve haver pelo menos 1 cliente!\n");
			return 0;
		}
	}
	return 1;
}
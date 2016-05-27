#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define PCS 3 	// Qtde de PCs disponívels
#define MAX 15	// Qtde máxima de clientes em espera

// Lista FIFO de cliente na em espera na lanhouse
typedef struct {
	int x;
	struct Cliente *next; 
} Client;

// Estrutura do semáforo
typedef struct {
	int value;
	struct Client *list;
}semaphore;

// Função executada quando um cliente quer usar um PC
void* wait(semaphore *S);

// Fũnção executada quando um cliente deixa de usar um PC
void* signal(semaphore *S);

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



	return 0;
}

void* wait(semaphore *S){

}

void* signal(semaphore *S){

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
		gX = atoi(argv[1]);
		
		if(argv[1]<1){ 
			printf("Deve haver pelo menos 1 cliente!\n");
			return 0;
		}
	}
	return 1;
}
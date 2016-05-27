#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//#include <semaphore.h>

#define PCS 3 	// Qtde de PCs disponívels
#define MAX 15	// Qtde máxima de clientes em espera

// Variável global para armazenar a qtde de clientes
int gQtde = 0;

// Lista FIFO de cliente na em espera na lanhouse
typedef struct {
	int num;
	struct Cliente *next; 
} Client;

// Estrutura do semáforo
typedef struct {
	int value;
	struct Client *list;
}semaphore;

// Função para criar fila de espera para clientes
void* createFifo(struct Client *C);

// Função para inserção de clientes na fila de espera
void* insertClient(struct Client *C);

// Funçaõ para remoção de clientes da fila de espera
void* removeClient(struct Client *C);

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

	int i;
	pthread_t tPC[PCS]; 		// Cria lista de threads de PCS
	pthread_t tClient[gQtde];	// Cria lista de threads de Clientes

	for(i=0; i<PCS; i++)
		pthread_create(&tPC[i], NULL, funcThread, (void*)i);

	for(i=0; i<gQtde; i++)
		pthread_create(&tPC[i], NULL, funcThread, (void*)i);

	return 0;
}

void* createFifo(struct Client *C){
	*C = NULL;
}

void* insertClient(struct Client *C){
	if(C->num >= MAX)
		return 0;

	Client *newC;
	newC = (Client*) malloc(sizeof(Client));
	if(C == NULL)
		newC->num = 0;
	else
		newC->num = C->num+1;
	newc->next = C;
	C = newcC;

	return 1;
}

void* removeClient(struct Client *C){
	Client *old;
	old = C->next;
	free(C);
	C = old;
}

void* wait(semaphore *S){
	S->value--;
	if(S->value<0){
		insertClient(S->list);
		//block();
	}
}

void* signal(semaphore *S){
	S->value++;
	if(S->value<=0){
		removeClient(S->list);
		//wakeup(P);
	}
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
		gQtde = atoi(argv[1]);
		
		if(gQtde<1){ 
			printf("Deve haver pelo menos 1 cliente!\n");
			return 0;
		}
	}
	return 1;
}
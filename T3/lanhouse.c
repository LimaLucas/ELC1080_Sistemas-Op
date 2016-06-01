#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define PCS 3 	// Qtde de PCs disponívels
#define MAX 15	// Qtde máxima de clientes em espera

typedef struct client{
	int id;
	pthread_t thread;
} Client;

typedef struct pc{
	int id;
	int user; // Corresponde ao id do cliente que está usando
	struct timespec time_off;
	pthread_t thread;
} PC;

// Variável global para armazenar a qtde de clientes
int gQtdeM, gQtde = 0;
PC* gPCS[PCS]; // PCs disponíveis na lanhouse (SC)
// sem_t mutex;

// Thread para utilização de cada PC
void* threadPC(void* x);

// Thread para chegada de cada cliente
void* threadClient(void* x);

// Função que retorna o id do PC livre a + tempo, se não houver -1
int idFreePC();

// Função que calcula a diferença entre tempo inicial e final
double difTime(struct timespec t0, struct timespec t1);

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char** argv){
	if(!testInput(argc, argv))
		return -1;

	int i;
	Client* tClient[gQtde];	// Cria lista de threads de Clientes
	gQtdeM = gQtde;
	// sem_init(&mutex, 0, 1);

	printf("\n----- Lan House aberta!\n");

	// Criação das threads PCs e thrads Clientes
	for(i=0; i<PCS; i++){
		pthread_create(&gPCS[i]->thread, NULL, threadPC, (void*)i);
	}

	for(i=0; i<gQtdeM; i++){
		tClient[i]->id = i;
		pthread_create(&tClient[i]->thread, NULL, threadClient, (void*)tClient[i]);
	}

	// Junção das threads Clientes e thrads PCs
	for(i=0; i<gQtdeM; i++)
		pthread_join(tClient[i]->thread, NULL);
	for(i=0; i<PCS; i++)
		pthread_join(gPCS[i]->thread, NULL);

	// sem_destroy(&mutex);

	printf("Todos os clientes foram embora.\n----- Lan House fechada!\n");

	return 0;
}

void* threadPC(void* x){
	int i = (int) x;
	int q = 0;

	gPCS[i]->id = i;
	gPCS[i]->user = -1;
	clock_gettime(CLOCK_MONOTONIC_RAW, &gPCS[i]->time_off);
	while(gQtde > 0){
		// Verifica se há algum user no PC e se a quantidade de cliente diminuiu
		if(gQtde != q && gPCS[i]->user == -1){
			printf("\tPC\t%i\tdesligado.\n", gPCS[i]->id);
			q = gQtde;
		}
	}
	// sem_wait(&mutex);
	// SC
	// sem_post(&mutex);
}

void* threadClient(void* x){
	Client* C = (Client*) x;
	int freePC;

	sleep(10*((rand()%4)+1)); // Sleep para chegada aleatória dos clientes
	printf("\tCliente\t%i\tchegou\n", C->id);

	if(false) // Verifica se a fila de espera está cheia
		printf("\tCliente\t%i\tsaiu - Fila cheia\n", C->id);

	// SC
	if(freePC = idFreePC() != -1){
		gPCS[freePC]->user = C->id; // Guarda id do cliente utilizando o PC
		printf("\tCliente\t%i\tusando PC\t%i\n", C->id, freePC);
		sleep(80+rand()%9); // Sleep para controlar tempo de uso dos PCs
	}
	// sem_wait(&mutex);
	// SC
	// sem_post(&mutex);
	printf("\tCliente\t%i\tterminou de usar o PC e saiu\n", C->id);
	gQtde--;
}

int idFreePC(){
	int i, id = -1;
	struct timespec t = gPCS[0]->time_off;
	for(i=0; i<PCS; i++){
		// Verifica se há user no PC e se o tempo desligado é menor que o anterior
		if(gPCS[0]->user < 0 && difTime(t, gPCS[i]->time_off) <= 0) {
			t = gPCS[i]->time_off;
			id = i;
		}
	}
	return id;
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

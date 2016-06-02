#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define PCS 3 	// Qtde de PCs disponívels
#define MAX 15	// Qtde máxima de clientes em espera

typedef struct pc{
	int id;
	int user; // Id do cliente que está usando o PC no momento
	time_t time_off; // Tempo em que o PC foi desligado e pode ser usado
} PC;

int gQtde = 0; // Variável global para armazenar a qtde de clientes
int gFila = 0; // Variável global para controlar a fila de espera
PC* gPCS; // PCs disponíveis na lanhouse (SC)

sem_t mutex; // Semáforo para controle da sessão crítica do PC
sem_t mutexFila; // Semáforo para controle da sessão crítica da fila

// Thread para chegada de cada cliente
void* threadClient(void* x);

// Função que retorna o id do PC livre a + tempo, se não houver -1
int idOldPC();

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

int main(int argc, char** argv){
	if(!testInput(argc, argv))
		return -1;

	// Para gerar um novo valor aleatório a cada execução
	srand(time(NULL));

	int i;

	gPCS = (PC*) calloc(PCS, sizeof(PC));
	pthread_t tClient[gQtde];

	printf("\n----- Lan House aberta!\n");

	// Inicialização dos semáforos
	sem_init(&mutex, 0, PCS);
	sem_init(&mutexFila, 0, 1);

	// Criação dos PCs
	for(i=0; i<PCS; i++){
		gPCS[i].id = i;
		gPCS[i].user = -1;
		gPCS[i].time_off = time(NULL)%10;
		sleep(1); // Sleep para cada PC tenha um tempo diferente
	}

	// Criação das threads Clientes
	for(i=0; i<gQtde; i++)
		pthread_create(&tClient[i], NULL, threadClient, (void*)i);
	
	// Junção das threads Clientes
	for(i=0; i<gQtde; i++)
		pthread_join(tClient[i], NULL);

	printf("Todos os clientes foram embora.\n----- Lan House fechada!\n");
	
	// Destruição dos semáforos
	sem_destroy(&mutex);
	sem_destroy(&mutexFila);

	return 0;
}

void* threadClient(void* x){
	int oldPC, t, id = (int) x;

	t = ((rand()%5)+1)*10;

	usleep(10000*t); // Sleep para chegada aleatória dos clientes
	
	sem_wait(&mutexFila);
	// Início da sessão crítica da fila
	if(gFila >= MAX){ // Verifica se a fila de espera está cheia
		printf(" - Cliente\t%i\tsaiu\t- Fila cheia\n", id);
		sem_post(&mutexFila); // Libera SC da fila caso ela esteja cheia
		pthread_exit(NULL);
	}else
		gFila++;
	// Fim da sessão crítica da fila
	sem_post(&mutexFila);
	
	printf(" - Cliente\t%i\tchegou\t- Tempo: %ims\n", id, t);

	sem_wait(&mutex);
	// Início da sessão crítica do PC
	oldPC = idOldPC();
	if(oldPC != -1){
		gPCS[oldPC].user = id; // Guarda id do cliente utilizando o PC
		gPCS[oldPC].time_off = time(NULL)%10; // Guarda tempo de início do uso
		
		t = (80+rand()%11); // Gera valor aleatóro entre 80 e 90 para tempo de uso

		printf(" - Cliente\t%i\tusando PC\t%i\t- Por: %ims\n", id, oldPC, t);
		usleep(t*1000); // Sleep para controlar tempo de uso dos PCs
		printf(" - Cliente\t%i\tterminou de usar o PC e saiu\n", id);

		gPCS[oldPC].user = -1; // Libera o uso do PC para outros usuários
		gPCS[oldPC].time_off += t; // Soma ao temp inicial o tempo de uso
	}
	// Fim da sessão crítica do PC
	sem_post(&mutex);

	sem_wait(&mutexFila);
	gFila--; // Sessão crítica da fila
	sem_post(&mutexFila);

	pthread_exit(NULL);
}

int idOldPC(){
	int i, id = -1;
	time_t t = gPCS[0].time_off;
	for(i=0; i<PCS; i++){
		// Verifica se há user no PC e se o time_off é menor que os anteriores
		if(gPCS[0].user < 0 && t >= gPCS[i].time_off) {
			t = gPCS[i].time_off;
			id = i;
		}
	}
	return id;
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
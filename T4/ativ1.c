#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define N 5 // Tamanho do buffer

int gBuffer[N]; // Variável global buffer de N posições (SC)
// Semáforos
sem_t full;  // Controla as posições ocupadas no Buffer - inicia com 0
sem_t empty; // Controla as posições vazias no Buffer - inicia com N
sem_t mutex; // Controla o acesso ao Buffer - inicia com 1

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

// Verifica se um númro é primo
int testPrime(int number);

// Thread produtora
void* threadProducer(void* x);

// Thread consumidora
void* threadConsumer(void* x);

int main(int argc, char** argv){
	if(!testInput(argc, argv))
		return -1;

	

	return 0;
}

void* threadConsumer(void* x){

}

void* threadProducer(void* x){

}

int testPrime(int number){
	int i, max, flag = 1;

	if(number%2>0){
		max = ceil(sqrt(number));
		for(i=2; i<=max; i++)
			if(number%i==0){
				flag = 0;
				break;
			}
	}
	return flag;
}

int testInput(int argc, char **argv){
	if(argc!=1){
		printf("Não deve ser informado nenhum parâmetro!\n");
		return 0;
	}
	return 1;
}
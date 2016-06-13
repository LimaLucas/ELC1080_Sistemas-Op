#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5  // Tamanho do buffer
#define Q 25 // Qtde de números da seq Fibonacci

int gBuffer[N]; // Variável global buffer de N posições (SC)
// Declaração dos semáforos
sem_t full;  // Controla as posições ocupadas no Buffer - inicia com 0
sem_t empty; // Controla as posições vazias no Buffer - inicia com N
sem_t mutex; // Controla o acesso ao Buffer - inicia com 1

// Função que verifica se os parâmetros de entrada estão corretos
int testInput(int argc, char **argv);

// Função sqrt, para evitar o uso da <math.h> e alterar o comando de compilação
// Não retorna o valor exato para valores muito altos, mas uma boa aproximaçao
float sqrtof(float x);

// Verifica se um númro é primo
int testPrime(int number);

// Thread produtora
void* threadProducer();

// Thread consumidora
void* threadConsumer();

int main(int argc, char** argv){
	if(!testInput(argc, argv))
		return -1;

	pthread_t tProducer;
	pthread_t tConsumer;

	// Inicialização dos semáforos
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, N);
	sem_init(&mutex, 0, 1);

	printf("----- Iniciando produção de %i números para consumo.\n", Q);

	// Criação das Threads - Produtoras e Consumidoras
	pthread_create(&tProducer, NULL, threadProducer, NULL);
	pthread_create(&tConsumer, NULL, threadConsumer, NULL);

	// Junção das Threads - Produtoras e Consumidoras
	pthread_join(tProducer, NULL);
	pthread_join(tConsumer, NULL);

	printf("----- Todos os %i números produzidos e consumidos.\n", Q);

	// Destruição dos semáforos
	sem_destroy(&full);
	sem_destroy(&empty);
	sem_destroy(&mutex);

	return 0;
}

void* threadConsumer(){

	sem_wait(&full);
	sem_wait(&mutex); // Início da SC

	// SC
	
	sem_post(&mutex); // Fim da SC
	sem_post(&empty);

}

void* threadProducer(){
	int i;
	int n2 = 0;
	int n1 = 1;

	for(i==0; i<Q; i++){
			sem_wait(&empty);
			sem_wait(&mutex); // Início da SC
			
			// SC

			sem_post(&mutex); // Fim da SC
			sem_post(&full);
			
			n1 += n2;
			n2 = n1 - n2;
	}
	
	pthread_exit(NULL);
}

int testPrime(int X){
	int i, max;

	// Elimina direto os números pares e o 1
	if( (X!=2 && X%2==0) || X==1)
		return 0;
	else{
		// Reduz considerávelmente a qtde de números verificados
		max = (int) (sqrtof(X));
		// Verifica todos os possíveis divisores até a raiz quadrada de X
		for(i=2; i<=max; i++)
			// No primeiro divisor perfeito, retorna 0
			if(X%i==0){
				return 0;
			}
	}
	// Se não houver nenhum divisor perfeito (além de 1 e de X) retorna 1
	return 1;
}

float sqrtof(float x){
    // if(x <= 0) return 0; // 0 não será usado
    int i;
    float r = x;
    // Quanto maior o laço, maior a precisão
    for(i=0; i<10; ++i)
          r = r/2 + x/(2*r);
    
    return r;
}

int testInput(int argc, char **argv){
	if(argc!=1){
		printf("Não deve ser informado nenhum parâmetro!\n");
		return 0;
	}
	return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5  // Tamanho do buffer
#define Q 25 // Qtde de números da seq Fibonacci

int gBuffer[N]; // Variável buffer de N posições (SC)
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

	int i;
	pthread_t tProducer;
	pthread_t tConsumer;

	// Inicialização dos semáforos
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, N);
	sem_init(&mutex, 0, 1);

	// Inicialização do buffer com 0
	for(i=0; i<N; i++)
		gBuffer[i] = 0;

	printf("----- Iniciando produção de %i números para consumo.\n", Q);

	// Criação das Threads - Produtoras e Consumidoras
	pthread_create(&tProducer, NULL, threadProducer, NULL);
	pthread_create(&tConsumer, NULL, threadConsumer, NULL);

	// Junção das Threads - Produtoras e Consumidoras
	pthread_join(tProducer, NULL);
	pthread_join(tConsumer, NULL);

	printf("----- Todos os %i números produzidos foram consumidos.\n", Q);

	// Destruição dos semáforos
	sem_destroy(&full);
	sem_destroy(&empty);
	sem_destroy(&mutex);

	return 0;
}

void* threadConsumer(){
	int i, j, n;

	for(i=0; i<Q; i++){
		n = 0;

		sem_wait(&full);
		sem_wait(&mutex); // Início da SC -------

		for(j=0; j<N; j++) // Seleciona a posição com menor número no buffer
			if((gBuffer[n] > gBuffer[j] && gBuffer[j] != 0) || gBuffer[n] == 0)
				n = j;
		j = n;

		n = gBuffer[j]; // Salva item do buffer
		gBuffer[j] = 0; // Remove item do buffer
		printf("\t\t- Removido item %5i \n", n);
		
		sem_post(&mutex); // Fim da SC ----------
		sem_post(&empty);

		if(testPrime(n)) // Consome item (verifica se é primo)
			printf("\t\t- Consumido item %5i (primo)\n", n);
		else
			printf("\t\t- Consumido item %5i \n", n);
	}
	pthread_exit(NULL);
}

void* threadProducer(){
	int i, j;
	int n2 = 0;
	int n1 = 1;

	for(i=0; i<Q; i++){

		sem_wait(&empty);
		sem_wait(&mutex); // Início da SC -------

		for(j=0; j<N; j++) // Seleciona primeira posição livre no buffer
			if(gBuffer[j] == 0)
				break;
		
		gBuffer[j] = n1; // Insere o item no buffer
		printf("\t- Produzido o item %5i na posição %2i \n", n1, j);

		sem_post(&mutex); // Fim da SC ----------
		sem_post(&full);
		
		// Cálculo dos números da sequência Fibonacci fora da SC
		n1 += n2;
		n2 = n1 - n2;
	}
	pthread_exit(NULL);
}

int testPrime(int n){
	int i, max;

	// Elimina direto os números pares e o 1
	if( (n!=2 && n%2==0) || n==1)
		return 0;
	else{
		// Reduz considerávelmente a qtde de números verificados
		max = (int) (sqrtof(n));
		// Verifica todos os possíveis divisores até a raiz quadrada de n
		for(i=2; i<=max; i++)
			// No primeiro divisor perfeito, retorna 0
			if(n%i==0){
				return 0;
			}
	}
	// Se não houver nenhum divisor perfeito (além de 1 e de n) retorna 1
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
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5  // Tamanho do buffer
#define Q 25 // Qtde de números da seq Fibonacci

int gBuffer[N]; // Variável global buffer de N posições (SC)
int gQtde = 0; // Variável global para armazenar a qtde de Consumidores
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

int testPrime(int X){
	int i, max;

	// Elimina direto os números pares
	if(X%2>0){
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
	if(argc!=2){
		printf("Informe o número de consumidores!\n");
		return 0;
	}else{
		sscanf(argv[1], "%i", &gQtde);
		
		if(gQtde<1){ 
			printf("Deve haver pelo menos 1 consumidor!\n");
			return 0;
		}
	}
	return 1;
}
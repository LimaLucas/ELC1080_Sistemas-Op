#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void fibonacci(int qtd){
	int i, f1, f2, aux;
	
	f1 = 0;
	f2 = 1;

	for(i==0; i<qtd; i++){
		if(i==0 || i==1)
			printf("%i ", i);
		else{
			printf("%i ", f1 + f2);
			aux = f2;
			f2 = f1 + f2;
			f1 = aux;
		}
	}
}

int main(int argc, char **argv){

	if(argc == 0){
		printf("Informe a quantidade de números!\n");
		return -1;
	}else if(atoi(argv[1]) < 0){
		printf("Infome um número positivo!\n");
		return -1;
	}else if(argc > 2){
		printf("Informe apenas um número!\n");
		return -1;
	}

	int status;
	pid_t id;
	
	printf("\n> P1 = %i, meu pai é %i\n  Criando filho...\n", getpid(), getppid());

	id= fork();
	if(id == -1) return 1;
	wait(&status);

	if(id == 0){
		printf("\n >> P2 = %i, meu pai é %i\n    Sequência Fibonacci: ", getpid(), getppid());
		fibonacci(atoi(argv[1]));
		printf("\n\n > P2 Morreu %i\n", getpid());
		return 0;

	}else{
		printf("\n> P1 Morreu %i\n\n", getpid());
		return 0;
	}
}
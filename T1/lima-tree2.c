#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

double difTime(struct timespec t0, struct timespec t1){
    return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int main(){

	struct timespec t0, t1;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

	int status, i;
	pid_t id;

	id = fork();
	if(id == -1) return -1;

	for(i=1; i<=7; i++){
		if(id == 0){
			printf("\n > P%i = %i, meu pai é %i\n", i, getpid(), getppid());
			id = fork();
			if(id == -1) return -1;
		}else{
			wait(&status);
			printf("\n > P%i Morreu %i\n", i, getpid());
			if(i == 1){
				clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
			 	printf("\n Tempo de execução: %lf\n\n", difTime(t0, t1));
			}
			return 0;
		}
	}
}
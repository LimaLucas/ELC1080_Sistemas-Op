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


	clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
	printf("Tempo de execução: %lf \n", difTime(t0, t1));
	return 0;
}
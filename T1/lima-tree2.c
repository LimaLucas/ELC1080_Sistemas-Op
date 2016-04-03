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

	int status;
	pid_t id;

	printf("\n> P1 = %i\n", getpid());

	id = fork();
	if(id == -1) return 1;
	wait(&status);

	if(id == 0){
		printf("\n > P2 = %i, meu pai é %i\n", getpid(), getppid());

		id = fork();
		if(id == -1) return 1;
		wait(&status);

		if(id == 0){
			printf("\n  > P3 = %i, meu pai é %i\n", getpid(), getppid());

			id = fork();
			if(id == -1) return 1;
			wait(&status);

			if(id == 0){
				printf("\n   > P4 = %i, meu pai é %i\n", getpid(), getppid());

				id = fork();
				if(id == -1) return 1;
				wait(&status);

				if(id == 0){
					printf("\n    > P5 = %i, meu pai é %i\n", getpid(), getppid());

					id = fork();
					if(id == -1) return 1;
					wait(&status);

					if(id == 0){
						printf("\n     > P6 = %i, meu pai é %i\n", getpid(), getppid());

						id = fork();
						if(id == -1) return 1;
						wait(&status);

						if(id == 0){
							printf("\n      > P7 = %i, meu pai é %i\n", getpid(), getppid());
							printf("\n      > P7 Morreu %i\n", getpid());
							return 0;

						}else{
							printf("\n     > P6 Morreu %i\n", getpid());
							return 0;
						}

					}else{
						printf("\n    > P5 Morreu %i\n", getpid());
						return 0;
					}
				}else{
					printf("\n   > P4 Morreu %i\n", getpid());
					return 0;
				}
			}else{
				printf("\n  > P3 Morreu %i\n", getpid());
				return 0;
			}
		}else{
			printf("\n > P2 Morreu %i\n", getpid());
			return 0;
		}

	}else{
		printf("\n> P1 Morreu %i\n", getpid());
		clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
		printf("\nTempo de execução: %lf\n\n", difTime(t0, t1));
		return 0;
	}
}
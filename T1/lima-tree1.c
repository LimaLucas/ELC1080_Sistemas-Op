#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <sys/wait.h>
#include <time.h>

double difTime(struct timespec t0, struct timespec t1){
    return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int main(){

	struct timespec t0, t1;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

	pid_t p2, p3, p4, p5, p6, p7;
	
	printf("> P1 = %i\n", getpid());

	p2 = fork();
	if(p2 == -1) return -1;
	if(p2 == 0){
		printf("  > P2 = %i, meu pai é %i\n", getpid(), getppid());
		sleep(1);
		
		p4 = fork();
		if(p4 == -1) return -1;
		if(p4 == 0){
			printf("    > P4 = %i, meu pai é %i\n", getpid(), getppid());
			sleep(1);
			printf("    > P4 Morreu %i \n", getpid());
			return 0;
		
		}else{
			p5 = fork();
			if(p5 == -1) return -1;
			if(p5 == 0){
				printf("    > P5 = %i, meu pai é %i\n", getpid(), getppid());
				sleep(1);
				printf("    > P5 Morreu %i\n", getpid());
				return 0;
			
			}else{
				wait(NULL);
			}
			wait(NULL);
		}
		printf("  > P2 Morreu %i\n", getpid());
		return 0;
		
	}else{
		p3 = fork();
		if(p3 == -1) return -1;
		if(p3 == 0){
			printf("  > P3 = %i, meu pai é %i\n", getpid(), getppid());
			sleep(1);

			p6 = fork();
			if(p6 == -1) return -1;
			if(p6 == 0){
				printf("    > P6 = %i, meu pai é %i\n", getpid(), getppid());
				sleep(1);
				printf("    > P6 Morreu %i\n", getpid());
				return 0;
			}else{
				p7 = fork();
				if(p7 == -1)return -1;
				if(p7 == 0){
					printf("    > P7 = %i, meu pai é %i\n", getpid(), getppid());
					sleep(1);
					printf("    > P7 Morreu %i\n", getpid());
					return 0;
				return 0;
				}else{
					wait(NULL);
				}
				wait(NULL);
			}
			printf("  > P3 Morreu %i\n", getpid());
			return 0;

		}else{
			wait(NULL);
		}
		wait(NULL);
	}
	printf("> P1 Morreu %i \n", getpid());

	clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
	printf("\nTempo de execução: %lf seg.\n\n", difTime(t0, t1));
	return 0;
}
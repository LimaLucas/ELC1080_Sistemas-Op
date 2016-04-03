#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){



	int status;
	pid_t id;
	
	printf("\n> P1 = %i\n", getpid());

	id = fork();
	if(id == -1) return 1;
	wait(&status);

	if(id == 0){
		printf("\n  >> P2 = %i, meu pai é %i\n", getpid(), getppid());
		
		id = fork();
		if(id == -1) return 1;
		wait(&status);

		if(id == 0){
			printf("\n    >>> P4 = %i, meu pai é %i\n", getpid(), getppid());
			wait(&status);
			printf("\n    >>> P4 Morreu %i\n", getpid());
			return 0;
		
		}else{
			id = fork();
			if(id == -1) return 1;
			wait(&status);
			
			if(id == 0){
				printf("\n    >>> P5 = %i, meu pai é %i\n", getpid(), getppid());
				wait(&status);
				printf("\n    >>> P5 Morreu %i\n", getpid());
				return 0;
			
			}else{
				printf("\n  >> P2 Morreu %i\n", getpid());
				return 0;
			}
		}
		
	}else{
		id = fork();
		if(id == -1) return 1;
		wait(&status);

		if(id == 0){
			printf("\n  >> P3 = %i, meu pai é %i\n", getpid(), getppid());
			
			id = fork();
			if(id == -1) return 1;
			wait(&status);

			if(id == 0){
				printf("\n    >>> P6 = %i, meu pai é %i\n", getpid(), getppid());
				wait(&status);
				printf("\n    >>> 6 Morreu %i\n", getpid());
				return 0;
			}else{
				id = fork();
				if(id == -1)return 1;
				wait(&status);

				if(id == 0){
					printf("\n    >>> P7 = %i, meu pai é %i\n", getpid(), getppid());
					printf("\n    >>> 7 Morreu %i\n", getpid());
					return 0;
				return 0;
				}else{
					printf("\n  >> P3 Morreu %i\n", getpid());
					return 0;
				}
			}

		}else{
			printf("\n> P1 Morreu %i \n", getpid());
			return 0;
		}
	}
}
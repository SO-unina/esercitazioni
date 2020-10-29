#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	int N=3, i, pid;
	for (i=0; i<N; i++){

		pid = fork();
		if (pid==0){
			printf("Sono il FIGLIO con PID: %d\n", getpid());
			i=3;
		}
	}
	printf("Istruzione successiva \n");
	return 0;
}

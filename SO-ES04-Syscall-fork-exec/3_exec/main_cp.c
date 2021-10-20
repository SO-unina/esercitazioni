#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char * argv[]) {

        int i, pid;

        pid = fork();

        if( pid == -1 ) {
                perror("fork fallita");
                exit(1);
        }

        if( pid == 0 ) {

                printf("Sono il processo figlio, con PID %d\n", getpid());
                printf("Command line passata al main():\n");
                printf("argv[0]: %s\n", argv[0]);
                printf("argv[1]: %s\n", argv[1]);
                printf("argv[2]: %s\n", argv[2]);
                printf("Attendo 3 secondi\n");

                for(i=0; i<3; i++) {
                        sleep(1);
                        printf(".\n");
                 }

                execl("/bin/cp", "cp", argv[1], argv[2], NULL);

                perror("Se arrivo in questo punto, qualcosa è andato storto...\n");

                kill(getppid(), SIGKILL);
                exit(1);

        } else {

                printf("Sono il processo padre, con PID %d\n", getpid());

                wait(NULL);

                printf("Copia effettuata con successo!\n");
                printf("Il processo padre termina\n");

                exit(0);
        }

        return 0;
}


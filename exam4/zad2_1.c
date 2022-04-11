#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>


int sumNumbers(char* arg){
    int num[4];
    int s = 0;
    FILE* f = fopen(arg, "rb");
    if (NULL == f){
        perror("error");
        exit(-1);
    }
    int i = 0;

    fscanf(f, "%d %d %d %d", &num[0], &num[1], &num[2], &num[3]);

    for (int i = 0; i < 4; i++){
        s += num[i];
    }
    fclose(f);
    return s;
    
}


int main(int argc, char* argv[]){
    static int sum = 0;
    int signal;
    int fd[2];
    pipe(fd);
    fd[0];
    fd[1];
    if (pipe(fd) == -1) {
        perror("pipe error");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < argc - 1; i++){
        pid_t pid = fork();
        if (0 == pid){
            sum += sumNumbers(argv[i + 1]);
            printf("sum = %d\n", sum);
            exit(EXIT_SUCCESS);
        }
        
    }
    for (int i = 0; i < argc - 1; i++){
        wait(&signal);
        printf("Sum = %d\n", sum);
    }
  
    return EXIT_SUCCESS;
}
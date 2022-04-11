#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

int sum = 0;

void* sumNumbers(void* arg){
    int num[4];
    FILE* f = fopen((char*)arg, "rb");
    if (NULL == f){
        perror("error");
        exit(-1);
    }
    int i = 0;

    fscanf(f, "%d %d %d %d", &num[0], &num[1], &num[2], &num[3]);

    for (int i = 0; i < 4; i++){
        sum += num[i];
    }

    fclose(f);
}
 int main(int argc, char* argv[]){
 pthread_t th[argc - 1]; 

    for (int i = 0; i < argc - 1; i++){
        
        if (pthread_create(th + i, NULL, &sumNumbers, argv[i + 1])){
            perror("create error");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < argc - 1; i++){
        if (pthread_join(th[i], NULL) != 0 ){
            perror("join error");
            return EXIT_FAILURE;
        }
    }

    printf("%d\n", sum);

    return EXIT_SUCCESS;
}
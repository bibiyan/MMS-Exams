#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

pthread_mutex_t mux;
sem_t sem;

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int* convertToArray(char* c)
{
	int len = strlen(c),i;
	int *a = (int*)malloc(len*sizeof(int));
	for(i = 0;i < len;i++)
		a[i] = c[i] - 48;
	return a;
}

char* intArrayToString(int *a){
	int n = sizeof(a) / sizeof(int);
	char *arrChar = (char *) malloc (sizeof(char) * (n + 1));
	for(int i = 0; i < n; i++)
		arrChar[i] = a[i] + '0';
	arrChar[n] = '\0';
}
void* sortNum(void* arg){

    char* str = (char*)arg;
    int index = 0;
    while (str[index] != ' '){
        index++;
    }
    index++;
    while (str[index] != ' '){
        index++;
    }

    char firstStr[index];
    for (int i = 0; i < index; i++){
        firstStr[i] = str[i];
    }
    firstStr[index] = '\n';

    int j = 0;
    char helper[strlen(str) - index - 1];
    for (int i = index + 1; i < strlen(str) ; i++){
        helper[j] = str[i];
        j++;
    }
    helper[j+1] = '\n';

    int* num = convertToArray(helper);
    int size = sizeof(num)/sizeof(num[0]);

    qsort(&num, size, sizeof(int), cmp);
    
    char* newString = intArrayToString(num);
    
    char* finalStr = strcat(firstStr, newString);
    return finalStr;

}

int main(){

    int N, M;
    printf("Enter N rows and M numbers: ");
    scanf("%d %d", &N, &M);
    
    char* filename;
    printf("Enter file name: ");
    scanf("%s ", &filename);
    int fd = open(filename, O_RDWR | O_TRUNC, 0777);
    if (-1 == fd){
        perror("error");
        return EXIT_FAILURE;
    }
    
    pthread_t th[N]; 

    char *row = malloc(sizeof(char*));
   
    for (int i = 0; i < N; i++){
        scanf("%s", &row);
        if (pthread_create(th + i, NULL, &sortNum, row) !=0){
            perror("create error");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < N; i++){
        void *res;
        if (pthread_join(th[i], &res) != 0 ){
            perror("join error");
            return EXIT_FAILURE;
        }
        write(fd, (char*)res, strlen(res));
    }

    return EXIT_SUCCESS;
}
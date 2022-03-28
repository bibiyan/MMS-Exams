#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countDigits(long long num){
    if (num <= 0){
        return 0;
    }
    return 1 + countDigits(num/10);
}

char changeSym(char c, int pos){
    if (pos%2 == 0){
        return c + 17;
    }
    else{
        switch(c){
            case '0':{return '!'; }
            case '1':{return '#'; }
            case '2':{return '/'; }
            case '3':{return '~'; }
            case '4':{return '='; }
            case '5':{return '`'; }
            case '6':{return '\\';}
            case '7':{return '>'; }
            case '8':{return '.'; }
            case '9':{return ','; }
        }
    }
}

int main(){
    long long num;
    printf("Enter number: ");
    scanf("%llu", &num);
    
    char snum[countDigits(num) + 1];
    sprintf(snum, "%lld", num);
    
    for (int i = 0; i < strlen(snum); i++){
        snum[i] = changeSym(snum[i], i);
    }
    for (int i = 0; i < strlen(snum); i++)
    {
        printf("%c", snum[i]);
    }
    return 0;
}
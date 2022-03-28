#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNT 10
#define MODELLEN 7
double randDouble(double min, double max){
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
int randInt(int min, int max){
    return min + rand() % (max - min +1);
}

typedef struct{
    char model[21];
    uint8_t maxspeed;
    double price;
}Car;

int compModelA(const void* car1, const void* car2){
    Car *c1 = (Car*) car1;
    Car *c2 = (Car*) car2;
    return strcmp(c1->model, c2->model);
}

int compModelD(const void* car1, const void* car2){
    Car *c1 = (Car*) car1;
    Car *c2 = (Car*) car2;
    return strcmp(c2->model, c1->model);    
}


int compPriceA(const void* car1, const void* car2){
    Car *c1 = (Car*) car1;
    Car *c2 = (Car*) car2;
     return (c1->price - c2->price); 
}

int compPriceD(const void* car1, const void* car2){
    Car *c1 = (Car*) car1;
    Car *c2 = (Car*) car2;
    return (c2->price - c1->price);    
}

int compMaxSpeedA(const void* car1, const void* car2){
    Car *c1 = (Car*) car1;
    Car *c2 = (Car*) car2;
     return (c1->maxspeed - c2->maxspeed); 
}

int compMaxSpeedD(const void* car1, const void* car2){
    Car *c1 = (Car*) car1;
    Car *c2 = (Car*) car2;
    return (c2->maxspeed - c1->maxspeed);    
}

int(*getComparator(int n))(const void*, const void*){
    switch(n){
        case 1:{ return compModelA;
                 break;}
        case 2:{ return compModelD;
                 break;}
        case 3:{ return compMaxSpeedA;
                 break;}
        case 4:{ return compMaxSpeedD;
                 break;}
        case 5:{ return compPriceA;
                 break;}
        case 6:{ return compPriceD;
                 break;}
        default: { return NULL; break;}
    }
}


void print(Car c){
    printf("Model: %s, ", c.model); 
    printf("Max speed: %u, ", c.maxspeed);
    printf("Price: %0.2lf ", c.price);
    printf("\n");
}
int main()
{
    srand(time(NULL));
    Car cars[COUNT];
    for (int i = 0; i < COUNT; i++){   
        cars[i].maxspeed = randInt(100,300);
        cars[i].price = randDouble(1000.00,1000000.00);
        cars[i].model[0] = randInt('A', 'Z');
        for (int j = 1; j < randInt(5, 10); j++){
            cars[i].model[j] = randInt('a', 'z');
        }
    }
    int opt;
    printf("Enter 1 - 6:");
    scanf("%d", &opt);
    qsort(cars, 10, sizeof(Car), getComparator(opt));

    for(int i = 0; i < COUNT; i++){
        print(cars[i]);
    }
    return 0;
}
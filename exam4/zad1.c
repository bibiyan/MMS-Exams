#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#define ITEM_COUNT 10

double randDouble(double min, double max){
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
int randInt(int min, int max){
    return min + rand() % (max - min +1);
}

typedef struct{
    uint16_t number;
    char *description;
    double weight;
    double price;

}Item;

typedef struct node {
    Item item;
    struct node* next;
} node_t;

void push(node_t** head, Item i){
    node_t* newItem = malloc(sizeof(node_t));
    newItem->item.number = i.number;
    strcpy(newItem->item.description, i.description);
    newItem->item.weight = i.weight;
    newItem->item.price = i.price;
    
    newItem->next = *head;
    *head = newItem;
}

double totalItemsWeight(node_t* items){
    if (items == NULL){
        return -1;
    }
    node_t* curr = items;
    double w = 0;
    while(curr){
        w += curr->item.weight;
        curr = curr -> next;
    }
    free(curr);
    return w;

}
node_t *minPriceItem(node_t* items){
    if (items == NULL){
        return NULL;
    }
    double minPrice = 0;
    node_t* curr = items;
    node_t* min = items;
    while(curr){
        if (minPrice > curr->item.price){
            minPrice = curr->item.price;
            min = curr;
        }
        curr = curr->next;
    }
    return min;
}

Item makeRndItem(){
    Item i;
    i.number = randInt(1, 32766);
    
    i.description[0]=randInt('A', 'Z');

    i.weight = randDouble(0.1, 100.00);
    i.price = randDouble(1,1500);
    
    /*int index = 0;
    for (int k = 0; k < randInt(5, 10); k++){

        for (int j = index + 1; j < randInt(1, 10); j++){
            i.description[j] = randInt('a', 'z');
            index = j + 1;
        }
        i.description[index] = ' ';
    }*/
    char string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    for (int j = 1; j < randInt(5, 50); j++){
        i.description[j] = string[rand()%(strlen(string))];
    
    }
    
    printf("%s\n", i.description);
    
    return i;
}

void printInfo(Item i){
    printf("Number: %d, ", i.number); 
    printf("Description: %s, ", i.description);
    printf("Weight: %lf, ", i.weight);
    printf("Price: %.2lf", i.price);
    printf("\n");
}

void print(node_t* head) {
    node_t* curr = head;
    while(curr != NULL){
        printInfo(curr->item);
        curr = curr -> next;
    }
    putchar('\n');
}

int main(){
    srand(time(NULL));
    node_t* items = NULL;
    for (int i = 0; i < ITEM_COUNT; i++){
        Item it = makeRndItem();
        push(&items, it);
    }
    print(items);
    printf("Sum of weights = %lf\n", totalItemsWeight(items));
    printInfo(minPriceItem(items)->item);

    return EXIT_SUCCESS;
}
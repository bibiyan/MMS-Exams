#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node_t;

void push(Node_t** list, int d){
    Node_t* newNode = malloc(sizeof(Node_t));
    newNode->data = d; 
    newNode->next = *list;
    *list = newNode;
}
void pop(Node_t** list){
    if (*list == NULL){
        return;
    }
    Node_t* temp = *list;
    *list = (*list)->next; 
    
}
void createCycle(Node_t **list){
    int num;
    Node_t *curr = *list;
    while(curr->next !=NULL){
        curr = curr->next;
    }
    curr->next = *list;
}

void print(Node_t* cll){
    Node_t* curr = cll;
    while (curr->next != cll){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    putchar('\n');
}

Node_t* insertNth(Node_t *cll, int skipCount, int newElem){
    Node_t* newCll = NULL;
    push(&newCll, newElem);
    if (skipCount == 0 || cll == NULL){
        cll = newCll;
        return cll;
    }
    Node_t* curr = cll;
    Node_t* prev = curr;
    while (skipCount--){
        
        prev = curr;
        curr = curr->next;
    }
    prev->next = newCll;
    newCll->next = curr;
    return newCll;
}
void deleteFirst(Node_t** list){
    if (*list == NULL){
        return;
    }
    
        Node_t* temp = *list;
        *list = (*list)->next;
        free(temp);
        return;
}
Node_t* insertAfter(Node_t *cll, int skipCount, int newElem){
    Node_t* cll2 = NULL;
    cll2 = insertNth(cll, skipCount, newElem);
    for (int i = 0; i < skipCount; i++){
      // deleteFirst(&cll2);
      pop(&cll2);
    }
    return cll2;
}

int main(){
    int N;
    printf("enter N:");
    scanf("%d", &N);
    Node_t* list=malloc(sizeof(Node_t) * N);
    for (int i = 0; i < N; i++){
        int num;
        scanf("%d", &num);
        push(&list, num);
    }
    createCycle(&list);
    print(list);

    Node_t* cll = insertAfter(list, 2, 11);
    
    print(cll);

    free(list);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COUNT 10

typedef struct point{
    double x;
    double y;
}point_t;

typedef struct rectangle{
    point_t A;
    point_t B;
}rectangle_t;

typedef struct node {
    rectangle_t rectangle;
    struct node* next;
} node_t;

double distance(point_t p1, point_t p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

double randDouble(double min, double max){
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void push(node_t** head, rectangle_t r){
    node_t* newRectangle = malloc(sizeof(node_t));
    newRectangle->rectangle.A.x = r.A.x;
    newRectangle->rectangle.A.y = r.A.y;
    newRectangle->rectangle.B.x = r.B.x;
    newRectangle->rectangle.B.y = r.B.y;
    newRectangle->next = *head;
    *head = newRectangle;
}

void popNth(node_t** list, size_t n){
    if (*list == NULL){
        fprintf(stderr, "Empty list!\n");
        return;
    }
    if (n == 0){
        node_t* temp = *list;
        *list = (*list)->next;
        free(temp);
        return;
    }
    node_t* curr = *list;
    node_t* prev = curr;
    while (curr && n--) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr);
}

double areaRects(node_t* list){
    if (list == NULL){
        return 0;
    }
    node_t* curr = list;
    double areas = 0;
    while(curr){
        areas += distance(curr->rectangle.A, curr->rectangle.B) * 2;
        curr = curr -> next;
    }
    free(curr);
    return areas;
}

rectangle_t makeRndRectangle(){
    rectangle_t random;
    random.A.x = randDouble(-10.00, 10.00);
    random.A.y = randDouble(-10.00, 10.00);
    random.B.x = randDouble(-10.00, 10.00);
    random.B.y = randDouble(-10.00, 10.00);
    return random;

}

void filterRects(node_t** list, double min, double max){
    if (list == NULL){
        fprintf(stderr, "Empty list!\n");
        return;
    }
    node_t* curr = *list;
    int num = 0;
    while(curr){
        if(distance(curr->rectangle.A, curr->rectangle.B) * 2 < min &&
            distance(curr->rectangle.A, curr->rectangle.B) * 2 > max){
                popNth(&list, num);
            }
        curr = curr->next;
        num++;
    }
    free(curr);
}


void printRect(rectangle_t r){
    printf("A(x) = %.2lf, A(y) = %.2lf, B(x) = %.2lf, B(y) = %.2lf\n", r.A.x, r.A.y, r.B.x, r.B.y);
}

void print(node_t* list){
    node_t* curr = list;
    while(curr != NULL){
        printRect(curr->rectangle);
        curr = curr -> next;
    }
    putchar('\n');
}

int main(){
    srand(time(NULL));
    node_t* rectangles = NULL;
        for (int i = 0; i < COUNT; i++){
            rectangle_t r = makeRndRectangle();
            push(&rectangles, r);
        }

    print(rectangles);
    //filterRects(rectangles, 5, 10);
    //print(rectangles);
    //double allAreas = areaRects(rectangles);
    //printf("Areas = %.2lf\n", allAreas);
    free(rectangles);

    return 0;
}
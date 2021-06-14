#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define NAMESIZE 30
#define DEPARTMENTSIZE 20
#define MAXPASSWORD 30
typedef struct
{
    char userName[MAXPASSWORD];
    char password[MAXPASSWORD];
} Login;
typedef struct student {
    long int ID;
    char name[NAMESIZE];
    char department[DEPARTMENTSIZE];
    float degree;
}Student;
typedef struct node {
    Student data;
    struct node* next;
}Node;
typedef struct linked {
    Node* top;
    int size;
}Linked;
//nagy
void insert(Student* record, Linked* pl);
int main() {

    return 0;
}
//order is function of the name
void insert(Student* record, Linked* pl) {
    Node* pn = (Node*)malloc(sizeof(Node));
    pn->next = NULL;
    pn->data.ID = record->ID;
    strcpy(pn->data.name, record->name);
    strcpy(pn->data.department, record->department);
    pn->data.degree = record->degree;
    Node* currentPtr = pl->top;
    Node* previousPtr = NULL;
    //to insert  node in order
    while (currentPtr != NULL && strcmp(currentPtr->data.name, record->name) == -1)
    {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
    }
    if (pl->top == NULL || previousPtr == NULL) {
        pn->next = pl->top;
        pl->top = pn;
    }
    else {
        previousPtr->next = pn;
        pn->next = currentPtr;
    }
    pl->size++;
}
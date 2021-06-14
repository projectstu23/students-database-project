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
int linkedEmpty(Linked* pl);
void display(Student* record) ;
void enterChoice(int* ch);
int main() {
    //nagy => files
    Student record;
    Linked student;
    Login user = { "admin","admin" }, userCheck;
    int choice;
    //if the file exist, Linked will read the file else it will do nothing beacuse it's first time
    FILE* fptr = fopen("students.dat","rb");
    createLinked(&student);
    //to read the file data alwaya in the beginning and make it easy to deal with the data
    if (fptr != NULL) {
        readFile(fptr, &student,&user, insert);
        fclose(fptr);
    }
    puts("\t\t\t\tWELCOME TO YOUR STUDENTS DATABASE");
    puts("\ntip,the default userName is \"admin\", default password is \"admin\"\nLOGIN");
    printf("%s", "username: ");
    gets(userCheck.userName);
    printf("%s", "password: ");
    gets(userCheck.password);
    //to check for password correctness
    while ((strcmp(user.userName,userCheck.userName))!=0 || (strcmp(user.password,userCheck.password))!=0 ) {
        puts("wrong user name or password,please try login again");
        printf("%s", "username: ");
        gets(userCheck.userName);
        printf("%s", "password: ");
        gets(userCheck.password);
    }
    system("clear");
    instructions();
    enterChoice(&choice);
     while(choice !=11){
        puts("\t\t\t\t*******************************");
         switch (choice) {
           case 2:
            //abdelrahman
            printf("enter student ID: ");
            scanf("%ld", &record.ID);
            while (record.ID <= 0)
            {
                puts("wrong input, ID must be bigger than zero ");
                printf("enter student ID: ");
                scanf("%ld", &record.ID);
            }
                //to clean input buffer
                while ((getchar()) != '\n');
                printf("%s", "enter student name: ");
                gets(record.name);
                printf("%s", "enter student deprtemnt: ");
                gets(record.department);
                printf("enter student last year degree: ");
                scanf("%f", &record.degree);
                insert(&record, &student);
                break;
        case 3:
            //kashs
            //check that the Linked is not empty
            if (linkedEmpty(&student)) {
                puts("database already free, there's no students to delete");
            }
            else {
                deleteAll(&student);
                remove("students.dat");
                if (student.top == NULL)
                {
                    puts("all students removed");
                }
                //to save the password user had change
                fptr = fopen("students.dat", "wb");
                    save(fptr, &student, &user);
                    fclose(fptr);
            }
            break;
         }
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
//afaf
int linkedEmpty(Linked* pl)
{
    return pl->top == NULL;
}
 //kashsh
void deleteAll(Linked* pl) {
    Node* pn = pl->top;
    while (pl->top != NULL) {
        pl->top = pl->top->next;
        free(pn);
        pn = pl->top;
    }
    pl->size = 0;
}
 //afaf
 void display(Student* record) {
        printf("%-15ld%-25s%-25s%-25.2f\n", record->ID, record->name, record->department,record->degree);
}
 //afaf
void enterChoice(int* ch)
{
    printf("%s", "enter your choice: ");
    scanf("%d", ch);
    //to make sure user enter correct input
    while (*ch < 1 || *ch >11) {
        puts("wrong input, choices must be between \'1\' and \'11\'");
        printf("%s", "enter your choice: ");
        scanf("%d", ch);
    }
}
void  traverseLinked(Linked* pl, void (*pf)(Student* record))
{
    Node* pn = pl->top;
    while (pn != NULL)
    {
        (*pf)(&pn->data);
        pn = pn->next;
    }
}

/*
 
Русская версия:
(Дата создания:28.01.2024)
Этот код был написан с целью обучения работы со структурами. 
Все вопросы или предложения писать на почту pleshakovroma13@gmail.com .
Код был запущен на ОС ArchLinux.
gcc version 13.2.1.
gcc <названия файла в котором сохранили код> -o <название файла(любое) которй получится в ходе компиляции> 
(gcc main.c -o main команда в моем случае)
 
*/
 
/*
 
English version:
(Date of creation: 01/28/2024)
This code was written for the purpose of teaching how to work with structures.
Please write all questions or suggestions to pleshakovroma13@gmail.com.
The code was run on ArchLinux OS.
gcc version 13.2.1.
gcc <name of the file in which the code exists> -o <name of the file (any) that will be executed during compilation>
(gcc main.c -o main in my case)
 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct Student{
    char name[20];
    int age;
    struct Student* next;
};
 
struct List{
    int value;
    int size;
    struct Student* head;
    struct Student* end;
    struct Student* (*get_student)(struct List*, int);
    void (*add_to_the_begin)(struct List*, char[20], int);
    void (*add_to_the_end)(struct List*, char[20], int);
    void (*insert)(struct List*, int, char[20], int);
    void (*swap)(struct List*, int, int);
    void (*print_list)(struct List*);
    void (*pop)(struct List*, int);
};
 
struct Student* get_student(struct List* list, int n);
struct List* init_list();
void add_to_the_begin(struct List*, char[20], int);
void add_to_the_end(struct List*, char[20], int);
void insert(struct List*, int, char[20], int);
void swap(struct List*, int, int);
void print_list(struct List*);
void pop(struct List*, int);
 
 
int main(){
 
    struct List* list = init_list();
    struct Student* temp;
    list->size = 0;
 
    list->head = NULL;
 
    char name[6][20] = {
        "Roman",
        "Kirill",
        "Maks",
        "Lena",
        "Liza",
        "Vika"
    };
 
    list->add_to_the_begin(list, name[0], 18);
    list->add_to_the_end(list, name[1], 21);
    list->add_to_the_begin(list, name[2], 19);
    list->insert(list, 3, name[3], 23);
    list->add_to_the_end(list, name[4], 34);
    list->add_to_the_begin(list, name[5], 12);
    list->add_to_the_begin(list, name[0], 10);
    list->add_to_the_begin(list, name[1], 43);
 
    list->print_list(list);
 
    printf("=======================================\n");
 
    list->pop(list, list->size);
 
    list->print_list(list);
 
    printf("=======================================\n");
 
    printf("head %d\n", list->head->age);
    printf("end %d\n", list->end->age);
 
    return 0;
}
 
void swap(struct List* list, int a, int b){
 
    if(a >= b) return;
 
    struct Student* first;
    struct Student* second;
    struct Student* temp_first;
    struct Student* temp_second;
 
    first = get_student(list, a);
    second = get_student(list, b);
 
    if(a != 1) temp_first = get_student(list, a-1);
    temp_second = get_student(list, b-1);
 
    if(a != 1) temp_first->next = second;
    temp_second->next = first;
 
    temp_first = first->next;
 
    first->next = second->next;
    second->next = temp_first;
 
    if(a == 1) list->head = second;
    if(b == list->size) list->end = first;
 
}
 
void pop(struct List* list, int n){
 
    struct Student* temp;
    struct Student* temp_next;
 
    temp = get_student(list, n);
 
    get_student(list, n-1)->next = temp->next;
 
    if(n == 1){
        list->head = temp->next;
    }else if(n == list->size) list->end = get_student(list, n-1);
 
    free(temp);
 
    list->size -= 1;
 
}
 
 
void insert(struct List* list, int n, char name[20], int age){
 
    struct Student* temp = malloc(sizeof(struct Student));
    struct Student* temp_first;
 
    if(n == 1 || (n+1) == list->size)return;
 
    temp->next = list->get_student(list, n);
 
    temp_first = list->get_student(list, n-1);
    temp_first->next = temp;
 
    strcpy(temp->name, name);
    temp->age = age;
 
    list->size += 1;
 
}
 
struct List* init_list(){
 
    struct List* list = malloc(sizeof(struct List));
 
    list->get_student = get_student;
    list->add_to_the_begin = add_to_the_begin;
    list->add_to_the_end = add_to_the_end;
    list->insert = insert;
    list->print_list = print_list;
    list->swap = swap;
    list->pop = pop;
 
    return list;
 
}
 
void add_to_the_begin(struct List* list, char name[20], int age){
 
    struct Student* temp = malloc(sizeof(struct Student));
 
    if(list->size == 0){
        list->end = temp;
        list->head = temp;
    }else{
        temp->next = list->head;
        list->head = temp;
    }
    strcpy(list->head->name, name);
    list->head->age = age;
 
    list->size += 1;
 
}
 
void add_to_the_end(struct List* list, char name[20], int age){
 
    struct Student* temp = malloc(sizeof(struct Student));
 
    strcpy(temp->name, name);
    temp->age = age;
    temp->next = NULL;
 
    if(list->size == 0){
        list->end = temp;
        list->head = temp;
    }else{
        list->end->next = temp;
        list->end = temp;
    }
 
    list->size += 1;
 
}
 
void print_list(struct List* list){
 
    struct Student* temp = list->head;
 
    for(int i = 1; i <= list->size; i++){
        printf("Your age is %d, your name is %s", temp->age, temp->name);
        temp = temp->next;
 
        printf("\n");
    }
}
 
 
struct Student* get_student(struct List* list, int n){
 
    struct Student* temp;
 
    temp = list->head;
 
    for(int i = 1;i < n;i++)
        temp = temp->next;
 
    return temp;
 
}

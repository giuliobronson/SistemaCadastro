/* DIRETIVAS PRÉ - PROCESSAMENTO */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS */
typedef struct course_students {
  char period[8];
  char students[50][8];
  struct course_students *nxt;
} CStudents;

typedef struct student_courses {
  char period[8];
  char courses[13][52];
  struct student_courses *nxt;
} SCourses;

typedef struct students {
  char id[8];
  char name[96];
  char cpf[16];
  struct students *nxt;
  struct student_courses *init_courses;
} TStudents;

typedef struct courses{
  char id[8];
  char name[52];
  char professors[96][16];
  struct courses *nxt;
  struct course_students *init_students;
} TCourses;

/* FUNÇÕES */
void insert_course_student(CStudents **initalPointer, char period[], char students[][8]) {
    CStudents *newElement = (CStudents *)malloc(sizeof(CStudents));
    strcpy(newElement->period, period);
    strcpy(newElement->students[0], students[0]);
    newElement->nxt = *initalPointer;
    *initalPointer = newElement;
}


void delete_student() {

}

void insert_course(TCourses **initialPointer, char courseId[], char courseName[], char courseProfessors[][16]) { //works
    TCourses *newElement = (TCourses *)malloc(sizeof(TCourses));
    strcpy(newElement -> id,courseId);
    strcpy(newElement -> name, courseName);
    strcpy(newElement -> professors[0], courseProfessors[0]);
    newElement -> init_students = NULL;
    newElement -> nxt = *initialPointer;
    *initialPointer = newElement;

}
//Retornar o próprio elemento da lista na busca
TCourses* find_course(TCourses *begin, char id[]) { //works
  while (begin) {
    if(strcmp(id, begin->id) == 0){
      return begin;
    }
    begin = begin->nxt;
  }
  
}

char** find_course_students(TCourses *begin, char course_id[], char period[]) {
    TCourses *targetCourse = (TCourses *)malloc(sizeof(TCourses));
    targetCourse = find_course(begin, course_id);
    while (targetCourse->init_students) {
      if(strcmp(period, targetCourse->init_students->period) == 0) {
        char **periodStudents = (char**)malloc(sizeof(char*));
        periodStudents = targetCourse->init_students->students;
        printf("Here: %s\n", targetCourse->init_students->students[0]);
        return periodStudents;
      }
      targetCourse->init_students = targetCourse->init_students->nxt;
    }   
}

void delete_course(TCourses **initialPointer, char id[]) { //works
  TCourses *aux = *initialPointer;
  TCourses *previous = NULL;
  while(aux) {
    if(strcmp(id, aux->id) == 0){
      break;
    }
    previous = aux;
    aux = aux->nxt;
  }

  if(aux){
    if(previous){
      previous->nxt = aux->nxt;
    }else *initialPointer = aux->nxt;
    free(aux);
  }
}



/* LOOP PRINCIPAL */
int main() {
    TCourses *begin = NULL;
    char id[8] = "1234";
    char name[52] = "Linear Algebra";
    char professors[1][16] = {"Zao"};

    char id2[8] = "4321";
    char name2[52] = "Calculus";
    char professors2[1][16] = {"Cerq"};
    insert_course(&begin, id, name, professors);
    insert_course(&begin, id2, name2, professors2);


    TCourses *target = (TCourses *)malloc(sizeof(TCourses));
    target = find_course(begin,"1234");
    char students[1][8] = {"20010"};
    insert_course_student(&(target->init_students), "2022.1",students);
    printf("%s\n", (target->init_students)->period);

    //Como printar o vetor de char de alunos?? Tomando core dumped na 123
    //printf("Aqui %s", find_course_students(begin,"1234","2022.1")[0]);
    find_course_students(begin,"1234","2022.1");

    TCourses *aux = begin;

    //imprimir valores
    while(aux) {
        printf("%s  was the id\n", aux->id);
        if(aux->init_students)
          printf("here is %s", aux->init_students->students[0]);
        aux = aux->nxt;
    }

    //liberar memoria
    aux = begin;
    while(aux) {
        TCourses *tmp = aux->nxt;
        free(aux);
        aux = tmp;
    }

    

    return 0;
}
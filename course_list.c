/* DIRETIVAS PRÉ - PROCESSAMENTO */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS */
typedef struct course_students {
  char period[8];
  char students[50][8];
  int studentsNumber;
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

void insert_course_student(char period[], char student[], char course[], TCourses *begin ) { //works
    TCourses *target = (TCourses *)malloc(sizeof(TCourses));
    target = find_course(begin,"1234");
    CStudents *aux = target->init_students;
    while(aux) {
      if(strcmp(period,aux->period) == 0) {
        int position = aux->studentsNumber;
        strcpy(aux->students[position], student);
        aux->studentsNumber++;
        return;
      }
      aux = aux->nxt;
    }


    CStudents *newElement = (CStudents *)malloc(sizeof(CStudents));
    strcpy(newElement->period, period);
    strcpy(newElement->students[0], student);
    newElement->studentsNumber = 1;
    newElement->nxt = target->init_students;
    target->init_students = newElement;
}

void print_course_students(TCourses *begin, char course_id[], char period[]) {
    TCourses *targetCourse;
    targetCourse = find_course(begin, course_id);
    while (targetCourse->init_students) {
      if(strcmp(period, targetCourse->init_students->period) == 0) {
        if(targetCourse->init_students->studentsNumber > 0){
          printf("Alunos: \n");
          for(int i = 0; i < targetCourse->init_students->studentsNumber; i++){
            printf("%s \n",targetCourse->init_students->students[i]);
          }
          return;
        }
      }
      targetCourse->init_students = targetCourse->init_students->nxt;
    }   
    printf("Não há alunos cadastrados nesse período\n");
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
    CStudents *aux2 = aux->init_students;
    while (aux2) {
      CStudents *temp = aux2;
      free(aux2);
      aux2 = temp->nxt;
    }
    
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
    insert_course_student("2022.1","20010", "1234", begin);
    insert_course_student("2022.1","20011", "1234", begin);
    insert_course_student("2022.2","20020", "1234", begin);
    printf("%s\n", (target->init_students)->students[0]);

    //Como printar o vetor de char de alunos?? Tomando core dumped na 123
    //printf("Aqui %s", find_course_students(begin,"1234","2022.1")[0]);
    print_course_students(begin,"1234","2021.2");

    TCourses *aux = begin;

    //imprimir valores
    // while(aux) {
    //     printf("%s  was the id\n", aux->id);
    //     if(aux->init_students)
    //       printf("here is %s", aux->init_students->students[0]);
    //     aux = aux->nxt;
    // }

    //liberar memoria
    aux = begin;
    while(aux) {
        TCourses *tmp = aux->nxt;
        free(aux);
        aux = tmp;
    }

    

    return 0;
}
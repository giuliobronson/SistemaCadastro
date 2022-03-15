/* DIRETIVAS PRÉ - PROCESSAMENTO */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS */
typedef struct course_students {
  char id[8];
  struct course_students *nxt;
};

typedef struct student_courses {
  char id[8];
  struct student_courses *nxt;
};

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
void insert_student(TStudents **ptr_init, char *id, char *name, char *cpf) {
  TStudents *new = (TStudents*)malloc(sizeof(TStudents));

  if(!new) {
    printf("Memória indisponível para alocação!");
    return;
  }

  strcpy(new->id, id);
  strcpy(new->name, name);
  strcpy(new->cpf, cpf);
  new->nxt = *ptr_init;
  *ptr_init = new;
}

void find_student() {

}

void delete_student() {

}

void insert_course() {

}

void find_course() {

}

void delete_course() {

}

/* LOOP PRINCIPAL */
int main() {
  TStudents *init_student = NULL;
  TCourses *init_course = NULL;

  do {
    int opt1;

    printf(
      "SISTEMA DE CADASTRO\n\n"
      "Qual cadastro deseja atualizar?\n"
      "[1] Aluno\n"
      "[2] Disciplina\n");
    printf("~ "); scanf("%d", &opt1);

    if(opt1 == 1) {
      int opt2;

      printf(
        "Cadastro de alunos\n\n"
        "Qual processo deseja realizar?\n"
        "[1] Cadastro de um novo aluno\n"
        "[2] Consulta de aluno cadastrado\n"
        "[3] Remoção de aluno cadastrado\n");
      printf("~ "); scanf("%d", &opt2);

      if(opt2 == 1) {
        char id[8];
        char name[96];
        char cpf[16];

        printf("Qual o id do aluno a ser cadastrado?\n");
        printf("~ "); scanf("%s", id); fflush(stdin);
        printf("Qual o nome do aluno a ser cadastrado?\n");
        printf("~ "); scanf("%s", name); fflush(stdin);
        printf("Qual o cpf do aluno a ser cadastrado?\n");
        printf("~ "); scanf("%s", cpf); fflush(stdin);

        insert_student(&init_student, id, name, cpf);
        TStudents *aux = init_student;
        while(aux) {
            printf("%s\n", aux->id);
            aux = aux->nxt;
        }
      } 
      else if(opt2 == 2) {
        /* find_student */
      }
      else if(opt2 == 3) {
        /* delete_student */
      }
      else {
        printf("Opção inválida!\n\n");
      }
    }
    else if(opt1 == 2) {
      int opt2;

      printf(
        "Cadastro de disciplina\n\n"
        "Qual processo deseja realizar?\n"
        "[1] Cadastro de uma nova disciplina\n"
        "[2] Consulta de disciplina cadastrada\n"
        "[3] Remoção de disciplina cadastrada\n");
      printf("~ "); scanf("%d", &opt2);

      if(opt2 == 1) {
        /* insert_course */
      }
      else if(opt2 == 2) {
        /* find_course */
      }
      else if(opt2 == 3) {
        /* delete_course */
      }
      else {
        printf("Opção inválida!\n\n");
      }
    }
    else {
      printf("Opção inválida!\n\n");
    }
  } while(1);

  return 0;
}
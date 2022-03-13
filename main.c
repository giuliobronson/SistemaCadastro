/* DIRETIVAS PRÉ - PROCESSAMENTO */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS */
typedef struct course_students {
  char id[8];
  struct course_students *nxt;
}

typedef struct student_courses {
  char id[8];
  struct students_courses *nxt;
}

typedef struct students {
  char id[8];
  char name[96];
  char cpf[16];
  struct students *nxt;
  struct students_courses *init_courses;
} TStudents;

typedef struct courses{
  char id[8];
  char name[52];
  char professors[96][16]
  struct courses *nxt;
  struct course_students *init_students;
} TCourses;

/* FUNÇÕES */
void insert_student() {
  
}

void find_student() {

}

void delete_student() {

}

void insert_course() {

}

void find_course() {

}

void delete_student() {

}

/* LOOP PRINCIPAL */
int main() {
  do {
    TStudents *init_student = NULL;
    TCourses *init_course = NULL;
    int opt1;

    printf(
      "SISTEMA DE CADASTRO\n\n"
      "Qual cadastro deseja atualizar?\n"
      "[1] Aluno\n"
      "[2] Disciplina\n");
    printf("~ "); scanf("%d", &opt1);

    switch(opt1) {
      int opt2;

      case 1:
        printf(
          "Cadastro de alunos\n\n"
          "Qual processo deseja realizar?\n"
          "[1] Cadastro de um novo aluno\n"
          "[2] Consulta de aluno cadastrado\n"
          "[3] Remoção de aluno cadastrado\n");
          printf("~ "); scanf("%d", &opt2);

          switch (opt2)
          {
          case 1:
            /* insert_student */
            break;
          case 2:
            /* find_student */
            break;
          case 3:
            /* delete_student */
            break;
          default:
            printf("Opção inválida!\n\n");
          }
        break;
      case 2:
        printf(
          "Cadastro de disciplina\n\n"
          "Qual processo deseja realizar?\n"
          "[1] Cadastro de uma nova disciplina\n"
          "[2] Consulta de disciplina cadastrada\n"
          "[3] Remoção de disciplina cadastrada\n");
          printf("~ "); scanf("%d", &opt2);

          switch (opt2)
          {
          case 1:
            /* insert_course */
            break;
          case 2:
            /* find_course */
            break;
          case 3:
            /* delete_course */
            break;
          default:
            printf("Opção inválida!\n\n");
          }
        break;
      default:
        printf("Opção inválida!\n\n");
    }
  } while(1);

  return 0;
}
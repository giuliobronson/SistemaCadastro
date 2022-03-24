/* DIRETIVAS PRÉ - PROCESSAMENTO */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS */
typedef struct course_students {
  char period[12];
  char id[128][8];
  struct course_students *nxt;
} TCourseStudents;

typedef struct student_courses {
  int n;
  char period[12];
  char name[128][52];
  struct student_courses *nxt;
} TStudentCourses;

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
void start_students(TStudents **ptr_init) {
  FILE *file;
  int read = 1;

  file = fopen("alunos.txt", "rb");
  if(file) {
    while(1) {
      TStudents *new = (TStudents*)malloc(sizeof(TStudents));
      if(fread(new, sizeof(TStudents), 1, file) == 0) break;
      new->nxt = *ptr_init;
      *ptr_init = new;
    }
  }
  else
    file = fopen("alunos.txt", "wb");
  fclose(file);
}

void insert_student(TStudents **ptr_init, char *id, char *name, char *cpf) {
  TStudents *new = (TStudents*)malloc(sizeof(TStudents));
  if(!new) {
    printf("Memória indisponível para alocação!\n");
    return;
  }

  strcpy(new->id, id);
  strcpy(new->name, name);
  strcpy(new->cpf, cpf);
  new->nxt = *ptr_init;
  *ptr_init = new;

  printf("\nAluno inserido com sucesso!\n");
}

TStudents* find_student(TStudents *ptr_init, char *id) {
  while(ptr_init) {
    if(strcmp(id, ptr_init->id) == 0) return ptr_init;
    ptr_init = ptr_init->nxt;
  }
  return NULL;
}

TStudentCourses* find_period_courses(TStudentCourses *ptr_init, char *period) {
  while(ptr_init) {
    if(strcmp(period, ptr_init->period) == 0) return ptr_init;
    ptr_init = ptr_init->nxt;
  }
  return NULL;
}

void delete_student(TStudents **ptr_init, char *id) {
  TStudents *node = *ptr_init, *prev;
  while(node) {
    if(strcmp(id, node->id) == 0) break;
    prev = node;
    node = node->nxt;
  }
  if(node) {
    if(prev) prev->nxt = node->nxt;
    else *ptr_init = node->nxt;

    TStudentCourses *aux = node->init_courses;
    while(aux) {
      TStudentCourses *tmp = aux->nxt;
      free(aux);
      aux = tmp;
    }

    free(node);

    printf("\nAluno removido com sucesso!\n");
    return;
  }
  
  printf("\nAluno não encontrado!\n");
}

void save(TStudents *ptr_init) {
  TStudents *aux = ptr_init;
  FILE *file;

  file = fopen("alunos.txt", "wb");
  if(!file) {
    printf("Erro no salvamento!\n");
    return;
  }
  fwrite(aux, sizeof(TStudents), 1, file);
  fclose(file);
  aux = aux->nxt;

  file = fopen("alunos.txt", "ab");
  if(!file) {
    printf("Erro no salvamento!\n");
    return;
  }
  while(aux) {
    fwrite(aux, sizeof(TStudents), 1, file);
    aux = aux->nxt;
  }
  fclose(file);
}

/* LOOP PRINCIPAL */
int main() {
  TStudents *init_student = NULL;
  TCourses *init_course = NULL;

  start_students(&init_student);

  do {
    int opt1;
    printf(
      "\nSISTEMA DE CADASTRO\n\n"
      "Qual cadastro deseja atualizar?\n"
      "[1] Aluno\n"
      "[2] Disciplina\n");
    printf("~ "); scanf("%d", &opt1);

    if(opt1 == 1) {
      while(1) {
        int opt2;

        printf(
          "\nCadastro de alunos\n\n"
          "Qual processo deseja realizar?\n"
          "[1] Cadastro de um novo aluno\n"
          "[2] Consulta de informações de aluno cadastrado\n"
          "[3] Remoção de aluno cadastrado\n"
          "[4] Salvar e sair\n");
        printf("~ "); scanf("%d", &opt2);

        if(opt2 == 1) {
          char id[8], name[96], cpf[16];

          printf("Qual o id do aluno a ser cadastrado?\n");
          printf("~ "); scanf("%s", id); getchar();
          printf("Qual o nome do aluno a ser cadastrado?\n");
          printf("~ "); fgets(name, 96, stdin); name[strlen(name) - 1] = '\0';
          printf("Qual o cpf do aluno a ser cadastrado?\n");
          printf("~ "); scanf("%s", cpf); getchar();

          insert_student(&init_student, id, name, cpf);
        }
        else if(opt2 == 2) {
          char id[8];
          
          printf("Insira o código do aluno\n");
          printf("~ "); scanf("%s", id); getchar();

          TStudents *student = find_student(init_student, id);
          if(student) {
            printf(
              "\nCódigo: %s\n"
              "Nome: %s\n"
              "CPF: %s\n", student->id, student->name, student->cpf);

            TStudentCourses *aux1 = student->init_courses;
            printf("Períodos Cursados: ");
            while(aux1) {
              printf(!aux1->nxt ? "%s, " : "%s", aux1->period);
              aux1 = aux1->nxt;
            }
            printf("\n");

            char period[8];

            printf("Insira o período que deseja visualizar as disciplinas do aluno\n");
            printf("~ "); scanf("%s", period); getchar();

            TStudentCourses *aux2 = find_period_courses(student->init_courses, period);
            if(aux2) {
              printf("%s:\n", aux2->period);
              for(int i = 0; i < aux2->n; i++) 
                printf("%s\n", aux2->name[i]);
            }
            else
              printf("\nPeríodo não cursado!\n");
          }
          else
            printf("\nAluno não encontrado!\n");
        }
        else if(opt2 == 3) {
          char id[8];

          printf("Qual o código do aluno que deseja remover?\n");
          printf("~ "); scanf("%s", id); getchar();

          delete_student(&init_student, id);
        }
        else if(opt2 == 4)
          save(init_student);
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
    else 
      printf("Opção inválida!\n");
  } while(1);

  return 0;
}
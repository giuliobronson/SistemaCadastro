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
  int coursesNumber;
  char period[12];
  char ids[16][8];
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
  char professors[16][96];
  int credits;
  struct courses *nxt;
  struct course_students *init_students;
} TCourses;

/* FUNÇÕES */

/* Funções de gerenciamento de estudantes*/
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

TStudents* find_student(TStudents *ptr_init, char *id) {
  while(ptr_init) {
    if(strcmp(id, ptr_init->id) == 0) return ptr_init;
    ptr_init = ptr_init->nxt;
  }
  return NULL;
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
  new->init_courses = NULL;
  new->nxt = *ptr_init;
  *ptr_init = new;

  printf("\nAluno inserido com sucesso!\n");
}

void insert_student_course(TStudents *ptr_init, char *course_id, char *student_id, char *period) {
  TStudents *student = find_student(ptr_init, student_id);
  
  TStudentCourses *aux = student->init_courses;
  while(aux) {
    if(strcmp(period, aux->period) == 0) {
      strcpy(aux->ids[aux->coursesNumber], course_id);
      aux->coursesNumber++;
      return;
    }
    aux = aux->nxt;
  }

  TStudentCourses *new = (TStudentCourses*)malloc(sizeof(TStudentCourses));
  strcpy(new->period, period);
  strcpy(new->ids[0], course_id);
  new->coursesNumber = 1;
  new->nxt = student->init_courses;
  student->init_courses = new;
}

void print_period_courses(TStudents *ptr_init, char *id, char *period) {
  TStudents *student = find_student(ptr_init, id);

  TStudentCourses *aux = student->init_courses;
  while(aux) {
    if(strcmp(period, aux->period) == 0) {
        printf("\nDisciplinas:\n");
        for(int i = 0; i < aux->coursesNumber; i++) 
          printf("%s\n", aux->ids[i]); // Printar os nomes futuramente
      return;
    }
    aux = aux->nxt;
  }
  printf("\nEsse aluno não cursou disciplinas nesse período\n");
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

void save_students(TStudents *ptr_init) {
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


/* Funções de gerenciamento de disciplinas */
void insert_course(TCourses **initialPointer, char courseId[], char courseName[], char courseProfessors[][96], int professorsNumbers, int credits) { //works
  TCourses *newElement = (TCourses *)malloc(sizeof(TCourses));
  strcpy(newElement -> id,courseId);
  strcpy(newElement -> name, courseName);
  for(int i = 0; i < professorsNumbers; i++) 
    strcpy(newElement->professors[i], courseProfessors[i]);
  newElement -> credits = credits;
  newElement -> init_students = NULL;
  newElement -> nxt = *initialPointer;
  *initialPointer = newElement;
  printf("\nDisciplina inserida com sucesso!\n");
}

TCourses* find_course(TCourses *begin, char id[]) { //works
  while (begin) {
    if(strcmp(id, begin->id) == 0){
      return begin;
    }
    begin = begin->nxt;
  }
  
}

void insert_course_student(char period[], char student[], char course[], TCourses *begin ) { //works
  if(!begin) {
    printf("\nNão há disciplinas disponíveis\n");
    return;
  }
  TCourses *target = find_course(begin, course);
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
  printf("\nDisciplina removida!\n");
}

/* LOOP PRINCIPAL */
int main() {
  TStudents *init_student = NULL;
  TCourses *init_course = NULL;

  start_students(&init_student);
  // insert_student_course(init_student, "1234", "20028", "2022.1");
  // insert_student_course(init_student, "1234", "20028", "2021.1");
  // insert_student_course(init_student, "4321", "20028", "2021.1");

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
          "[4] Cadastro de aluno em disciplina\n"
          "[5] Salvar e sair\n");
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
              printf(aux1->nxt ? "%s, " : "%s", aux1->period);
              aux1 = aux1->nxt;
            }
            printf("\n");

            char period[8];

            printf("Insira o período que deseja visualizar as disciplinas do aluno\n");
            printf("~ "); scanf("%s", period); getchar();

            print_period_courses(init_student, id, period);
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
        else if(opt2 == 4) {
          char course_id[8], student_id[8], period[8];

          printf("Qual o código da discipliana na qual você gostaria de realizar a matrícula?\n");
          printf("~ "); scanf("%s", course_id); getchar();
          printf("Qual o estudante você gostaria de matricular nessa disciplina?\n");
          printf("~ "); scanf("%s", student_id); getchar();
          printf("Em qual período ocorrerá a matrícula?\n");
          printf("~ "); scanf("%s", period); getchar();

          insert_course_student(period, student_id, course_id, init_course);
          insert_student_course(init_student, course_id, student_id, period);
        }
        else if(opt2 == 5) {
          save_students(init_student);
          break;
        }
      }
    }
    else if(opt1 == 2) {
      while(1) {
        int opt2;

        printf(
          "\nCadastro de disciplina\n\n"
          "Qual processo deseja realizar?\n"
          "[1] Cadastro de uma nova disciplina\n"
          "[2] Consulta de disciplina cadastrada\n"
          "[3] Remoção de disciplina cadastrada\n"
          "[4] Salvar e sair\n");
        printf("~ "); scanf("%d", &opt2);

        if(opt2 == 1) {
          int professorsNumbers, credits;
          char id[8], name[96], professors[16][96];

          printf("Qual o id da disciplina a ser cadastrada?\n");
          printf("~ "); scanf("%s", id); getchar();
          printf("Qual o nome da disciplina a ser cadastrada?\n");
          printf("~ "); fgets(name, 96, stdin); name[strlen(name) - 1] = '\0';
          printf("Quantos professores a displina tem?\n");
          printf("~ "); scanf("%d", &professorsNumbers); getchar();
          printf("Quais os nomes dos professores dessa disciplina?\n");
          for(int i = 0; i < professorsNumbers; i++) {
            printf("~ (%d) ", i + 1); fgets(professors[i], 96, stdin); professors[i][strlen(professors[i]) - 1] = '\0';
          }
          printf("Quantos créditos a displina tem?\n");
          printf("~ "); scanf("%d", &credits);

          insert_course(&init_course, id, name, professors, professorsNumbers, credits);
        }
        else if(opt2 == 2) {
          char id[8];
          
          printf("Insira o código da disciplina\n");
          printf("~ "); scanf("%s", id); getchar();

          TCourses *course = find_course(init_course, id);
          if(course) {
            printf(
              "\nCódigo: %s\n"
              "Nome: %s\n"
              "Créditos: %d\n", course->id, course->name, course->credits);
            int i = 0;
            while(course->professors[i][0] != '\0') {
              printf(course->professors[i + 1][0] != '\0' ? "%s, " : "%s\n", course->professors[i]);
              i++;
            }

            char period[8];

            printf("Insira o período que deseja visualizar os alunos da disciplina\n");
            printf("~ "); scanf("%s", period); getchar();

            print_course_students(init_course, id, period);
          }
          else
            printf("\nDisciplina não encontrada!\n");
        }
        else if(opt2 == 3) {
          char id[8];

          printf("Qual o código da disciplina que deseja remover?\n");
          printf("~ "); scanf("%s", id); getchar();

          delete_course(&init_course, id);
        }
        else if(opt2 == 4){
          break;
        }
        else {
          printf("Opção inválida!\n\n");
        }
      }
    }
    else 
      printf("Opção inválida!\n");
  } while(1);

  return 0;
}
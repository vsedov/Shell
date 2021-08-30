#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define PWD_AMMOUNT 1026

#define GetCurrentDir getcwd

bool compare(char ch[20], char *type) { return strcmp(ch, type) == 0; }

void current_pwd(char *pwd) {
  if (!getcwd(pwd, 100)) {
    perror("ERROR");
    exit(EXIT_FAILURE);
  } else
    printf("%s\n", pwd);
  exit(0);
}

void ls() {
  struct dirent *d;

  DIR *main_dir = opendir(".");

  if (!main_dir) {
    perror("Error cannot open");
    exit(EXIT_FAILURE);
  }

  while ((d = readdir(main_dir)) != NULL) {
    if (d->d_name[0] == '.')
      continue;
    printf("%s ", d->d_name);
  }
  printf("\n");
  exit(0);
}

void cd(char *ch1) {
  char pwd[PWD_AMMOUNT];
  int k;

  k = chdir(ch1);

  if (k == -1) {
    perror("Error");
    exit(EXIT_FAILURE);
  }
  getcwd(pwd, PWD_AMMOUNT);
  printf("%s\n", pwd);
  exit(0);
}
void make_dir(char *ch1) {

  char pwd[100];
  if (!getcwd(pwd, 100)) {
    perror("ERROR");
    exit(EXIT_FAILURE);
  }
  strcat(pwd, "/");
  strcat(pwd, ch1);
  if (mkdir(pwd, 0777) == -1) {
    perror("ERROR");
    exit(EXIT_FAILURE);
  }
  exit(0);
}
void remove_dir(char *ch1) {

  char pwd[100];
  if (!getcwd(pwd, 100)) {
    perror("ERROR");
    exit(EXIT_FAILURE);
  }
  strcat(pwd, "/");
  strcat(pwd, ch1);
  rmdir(pwd);
  exit(0);
}
int main(int argc, char *argv[]) {

  char ch[20], ch1[20], pwd[PWD_AMMOUNT];

  for (int i = 0; i < PWD_AMMOUNT; i++) {
    pwd[i] = ' ';
  }

  int f, pid, status;

start:
  printf("1. The list of available commands can be viewed by typing \"man \\ "
         "\" \n");
  printf("2. Any command which doesn't require an input should be provided an "
         "input \"\\\" \n");
  printf("For e.g. : ls should be written as \"ls \\ \" \n");
  printf("myshell>");
  scanf("%s%s", ch, ch1);

  if (compare(ch, "ls")) {
    f = 1;
  } else if (compare(ch, "pwd")) {
    f = 2;
  } else if (compare(ch, "mkdir")) {
    f = 3;
  } else if (compare(ch, "exit")) {
    exit(0);
  } else if (compare(ch, "cd")) {
    f = 4;
  } else if (compare(ch, "rmdir")) {
    f = 5;
  } else if (compare(ch, "man")) {
    f = 6;
  } else {
    f = 0;
  }

  pid_t pidv = fork();

  // we can now define the switch value

  // Operate this within the child process
  if (pidv == 0) {
    switch (f) {
    case 1:
      ls();
    case 2:
      current_pwd(pwd);
    case 3:
      make_dir(ch1);

    case 4:
      cd(ch1);

    case 5:
      remove_dir(ch1);

    case 6:
      printf("1.ls\n");
      printf("2.cd\n");
      printf("3.pwd\n");
      printf("4.mkdir\n");
      printf("5.rmdir\n");
      printf("6.man\n");
      printf("7.exit\n");
      exit(0);

    default:
      printf("%s is not recognized.\n", ch);
      exit(0);
    }

  } else if (pidv > 0) {
    sleep(1);
    pid_t child_pid = wait(&status);

    goto start;
  }
}

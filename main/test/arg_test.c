#include <stdio.h>

int main(int argc, char *argv[]) {
  int i = 0;

  printf("You have entered %d arguments  ", argc);

  for (i = 0; i < argc; i++) {
    printf(">%s<\t", argv[i]);
  }

  return 0;
}

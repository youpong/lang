#include "lang.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char *p;

noreturn void error(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  va_end(ap);

  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    error("no input program");
  }

  p = argv[1];

  char *delim = "";
  while (*p) {
    printf("%s%d", delim, eval(NULL));
    delim = " ";
  }
  printf("\n");

  return EXIT_SUCCESS;
}

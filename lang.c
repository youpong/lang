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

  int val;
  while (*p) {
    val = eval(NULL);
  }
  printf("%d\n", val);

  return EXIT_SUCCESS;
}

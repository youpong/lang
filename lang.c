#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

static char *p;

noreturn static void error() {
  exit(EXIT_FAILURE);
}

static void skip() {
  while (isspace(*p))
    p++;
}

static int eval() {
  int val;

  if (isdigit(*p)) {
    val = *p++ - '0';
    while (isdigit(*p)) {
      val = val * 10 + *p++ - '0';
    }
    return val;
  }

  error();
}

int main(int argc, char **argv) {
  p = argv[1];

  char *delim = "";
  while (*p) {
    skip();
    printf("%s%d", delim, eval());
    delim = " ";
  }
  printf("\n");

  return EXIT_SUCCESS;
}

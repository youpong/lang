#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

static char *p;

noreturn static void error() {
  exit(EXIT_FAILURE);
}

static int eval() {
  int val;

  if (isdigit(*p)) {
    val = *p++ - '0';
    while (*p) {
      val = val * 10 + *p++ - '0';
    }
    return val;
  }

  error();
}

int main(int argc, char **argv) {
  p = argv[1];

  while (*p) {
    printf("%d\n", eval());
  }

  return EXIT_SUCCESS;
}

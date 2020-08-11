#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

static char *p;

noreturn static void error(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  va_end(ap);

  exit(EXIT_FAILURE);
}

static void skip() {
  while (isspace(*p))
    p++;
}

static int eval() {
  int val;

  skip();

  if (*p == '\0') {
    error("Error: token expected");
  }

  if (isdigit(*p)) {
    val = *p++ - '0';
    while (isdigit(*p)) {
      val = val * 10 + *p++ - '0';
    }
    return val;
  }

  int op1, op2;
  if (*p == '+') {
    p++;
    op1 = eval();
    op2 = eval();
    return op1 + op2;
  } else if (*p == '-') {
    p++;
    op1 = eval();
    op2 = eval();
    return op1 - op2;
  } else if (*p == '*') {
    p++;
    op1 = eval();
    op2 = eval();
    return op1 * op2;
  } else if (*p == '/') {
    p++;
    op1 = eval();
    if ((op2 = eval()) == 0) {
      error("divided by 0");
    }
    return op1 / op2;
  }

  error("invalid character: %c", *p);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    error("no input program");
  }

  p = argv[1];

  char *delim = "";
  while (*p) {
    printf("%s%d", delim, eval());
    delim = " ";
  }
  printf("\n");

  return EXIT_SUCCESS;
}

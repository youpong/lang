#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

static int eval(int arg);

static char *p;
static char func[26][99 + 1];

noreturn static void error(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  va_end(ap);

  exit(EXIT_FAILURE);
}

static void read_until(char c, char *buf) {
  while (*p != c && *p != '\0') {
    *buf++ = *p++;
  }
  if (*p == '\0') {
    error("expected ']' before EOF");
  }
  p++;
  *buf = '\0';
}

static void expect(char c) {
  if (*p != c)
    error("'%c' expected: \"%s\"", c, p);
  p++;
}

static void skip() {
  while (isspace(*p))
    p++;
}

static int eval_string(char *code, int arg) {
  char *orig = p;
  p = code;
  int val = eval(arg);
  p = orig;
  return val;
}

static int eval(int arg) {
  int val;

  skip();

  if (*p == '\0') {
    error("Error: token expected");
  }

  // Functoin parameter
  if (*p == '.') {
    p++;
    return arg;
  }

  // Function definition
  if ('A' <= *p && *p <= 'Z' && *(p + 1) == '[') {
    char name = *p;
    p += 2;
    read_until(']', func[name - 'A']);
    return eval(arg);
  }

  // Function application
  if ('A' <= *p && *p <= 'Z' && *(p + 1) == '(') {
    char name = *p;
    p += 2;
    int newarg = eval(arg);
    expect(')');
    return eval_string(func[name - 'A'], newarg);
  }

  if (isdigit(*p)) {
    val = *p++ - '0';
    while (isdigit(*p)) {
      val = val * 10 + *p++ - '0';
    }
    return val;
  }

  if (strchr("+-*/", *p) != NULL) {
    char op = *p++;
    int op1 = eval(arg);
    int op2 = eval(arg);
    switch (op) {
    case '+':
      return op1 + op2;
    case '-':
      return op1 - op2;
    case '*':
      return op1 * op2;
    case '/':
      if (op2 == 0) {
        error("divided by 0");
      }
      return op1 / op2;
    }
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
    printf("%s%d", delim, eval(0));
    delim = " ";
  }
  printf("\n");

  return EXIT_SUCCESS;
}

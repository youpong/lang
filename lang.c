#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

static int eval(int *args);

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

static int eval_string(char *code, int *args) {
  int val;
  char *orig = p;
  p = code;
  while (*p) {
    val = eval(args);
  }
  p = orig;
  return val;
}

static int eval(int *args) {
  int val;

  skip();

  if (*p == '\0') {
    error("Error: token expected");
  }

  // Functoin parameter
  if ('a' <= *p && *p <= 'z') {
    if (args == NULL)
      error("cannot access var: %c", *p);

    return args[*p++ - 'a'];
  }

  // Build-in
  if ('P' == *p) {
    p++;
    expect('(');
    int val = eval(args);
    expect(')');
    printf("%d\n", val);
    return val;
  }

  // Function definition
  if ('A' <= *p && *p <= 'Z' && *(p + 1) == '[') {
    char name = *p;
    p += 2;
    read_until(']', func[name - 'A']);
    return eval(args);
  }

  // Function application
  if ('A' <= *p && *p <= 'Z' && *(p + 1) == '(') {
    int newargs[26];
    char name = *p;
    p += 2;

    int i = 0;
    for (skip(); *p != ')'; skip())
      newargs[i++] = eval(args);
    expect(')');
    return eval_string(func[name - 'A'], newargs);
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
    int op1 = eval(args);
    int op2 = eval(args);
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
    printf("%s%d", delim, eval(NULL));
    delim = " ";
  }
  printf("\n");

  return EXIT_SUCCESS;
}

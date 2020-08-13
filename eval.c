#include "lang.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int eval_expr(int *args);

static char func[26][99 + 1];

static void expect(char c) {
  if (*p != c)
    error("'%c' expected: \"%s\"", c, p);
  p++;
}

static void skip() {
  while (isspace(*p))
    p++;
}

static void read_until(char c, char *buf) {
  while (*p != c && *p != '\0') {
    *buf++ = *p++;
  }
  if (*p == '\0') {
    error("expected '%c' before EOF", c);
  }
  p++;
  *buf = '\0';
}

static int eval_string(char *code, int *args) {
  int val;
  char *orig = p;
  p = code;
  while (*p) {
    val = eval_expr(args);
  }
  p = orig;
  return val;
}

/*
 * Function definition
 * NAME '[' body ']'
 */
static void eval_func_def() {
  char name = *p++;
  expect('[');
  read_until(']', func[name - 'A']);
}

static int eval_expr(int *args) {
  skip();

  if (*p == '\0') {
    error("Error: token expected before EOF");
  }

  // Functoin parameter
  if ('a' <= *p && *p <= 'z') {
    if (args == NULL)
      error("Undefined variable: %c", *p);

    return args[*p++ - 'a'];
  }

  // Build-in function P
  if ('P' == *p) {
    p++;
    expect('(');
    int val = eval_expr(args);
    expect(')');
    printf("%d\n", val);
    return val;
  }

  // Function application
  if ('A' <= *p && *p <= 'Z' && *(p + 1) == '(') {
    int newargs[26];
    char name = *p++;
    expect('(');

    for (int *arg = newargs; *p != ')'; arg++)
      *arg = eval_expr(args);

    expect(')');
    return eval_string(func[name - 'A'], newargs);
  }

  if (isdigit(*p)) {
    int val = *p++ - '0';
    while (isdigit(*p)) {
      val = val * 10 + *p++ - '0';
    }
    return val;
  }

  if (strchr("+-*/", *p) != NULL) {
    char op = *p++;
    int op1 = eval_expr(args);
    int op2 = eval_expr(args);
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

  error("Syntax error: %s", p);
}

int eval() {
  skip();
  if ('A' <= *p && *p <= 'Z' && *(p + 1) == '[') {
    eval_func_def();
    return 0;
  }
  return eval_expr(NULL);
}

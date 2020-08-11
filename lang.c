#include <ctype.h>
#include <stdio.h>

char *p;

static int eval() {
  int val;

  if (isdigit(*p)) {
    val = *p++ - '0';
    while (*p) {
      val = val * 10 + *p++ - '0';
    }
  }

  return val;
}

int main(int argc, char **argv) {
  p = argv[1];

  while (*p) {
    printf("%d\n", eval());
  }

  return 0;
}

#include <stdio.h>

static int eval() {
  return 0;
}

int main(int argc, char **argv) {
  char **p;
  p= &argv[1];
  
  for (;*p; p++) {
    printf("%d\n", eval());
  }
  
  return 0;
}

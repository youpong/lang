#pragma once
#include <stdnoreturn.h>

extern char *p;

int eval(int *args);
noreturn void error(char *fmt, ...);

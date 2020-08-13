#pragma once
#include <stdnoreturn.h>

extern char *p;

int eval();
noreturn void error(char *fmt, ...);

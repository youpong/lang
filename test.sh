#!/bin/bash

LANG=C

function error() {
    echo "$@" >&2
    exit 1
}

function runtest() {
    echo -e "$1" > tmp.0
    ./lang "$2" > tmp.1
    cmp tmp.0 tmp.1 || error "$3"
}

runtest  0  0 "Error: $LINENO"
runtest 42 42 "Error: $LINENO"
runtest '1 2 3' '1 2 3' "Error: $LINENO"

runtest   3 '+ 1 2'             "Error: $LINENO"
runtest   6 '+ + 1 2 3'         "Error: $LINENO"
runtest   6 '++1 2 3'           "Error: $LINENO"

runtest   1 '- 5 4'             "Error: $LINENO"
runtest  -9 '- 6 + 7 8'         "Error: $LINENO"

runtest  90 '* 9 10'            "Error: $LINENO"
runtest 621 '* + 11 12 + 13 14' "Error: $LINENO"

runtest   3 '/ 15 5'            "Error: $LINENO"
runtest   2 '/ 16 6'            "Error: $LINENO"
runtest   0 '/  0 17'           "Error: $LINENO"

# Functions
runtest   1 'F[.]     F(1)'       "Error: $LINENO"
runtest   2 'F[+ . .] F(1)'       "Error: $LINENO"
runtest  36 'F[* . 2] F(18)'      "Error: $LINENO"
runtest 256 'F[* . .] F(F(F(2)))' "Error: $LINENO"

runtest 321 'F[* .  .] G[+ . .] - F(19) G(20)' "$LINENO"
runtest  42 'F[+ .  .] G[F(.)]       G(21)'    "$LINENO"
runtest  12 'F[+. 22] G[F(*. 23)] /G(24)F(25)' "$LINENO"

# Error
# 
# divided by 0
./lang '/ 18 0'     2>/dev/null && error "Error: $LINENO"
./lang '/ 19 - 7 7' 2>/dev/null && error "Error: $LINENO"

./lang a 2>/dev/null && error "Error: accept digit only"

./lang '+ 1' 2>/dev/null && error "Error: must not null"

./lang 2>/dev/null && error "Error: no input program"

./lang 'F[' 2>/dev/null \
    && error "Error: expect ']' before EOF"

./lang 'F[.] F(2]' 2>/dev/null \
    && error "Error: ')' expected: \"]]\""       

rm tmp.{0,1}

echo "Okay."

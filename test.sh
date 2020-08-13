#!/bin/bash

LANG=C

function error() {
    echo "Error: $@" >&2
    exit 1
}

function runtest() {
    echo -e "$1" > tmp.0
    ./lang "$2" > tmp.1
    cmp tmp.0 tmp.1 || error "$3"
}

runtest  0  0           "$LINENO"
runtest 42 42           "$LINENO"
runtest '1 2 3' '1 2 3' "$LINENO"

runtest   3 '+ 1 2'             "$LINENO"
runtest   6 '+ + 1 2 3'         "$LINENO"
runtest   6 '++1 2 3'           "$LINENO"

runtest   1 '- 5 4'             "$LINENO"
runtest  -9 '- 6 + 7 8'         "$LINENO"

runtest  90 '* 9 10'            "$LINENO"
runtest 621 '* + 11 12 + 13 14' "$LINENO"

runtest   3 '/ 15 5'            "$LINENO"
runtest   2 '/ 16 6'            "$LINENO"
runtest   0 '/  0 17'           "$LINENO"

# Functions
runtest  32 'F[32]    F()'        "$LINENO"     
runtest   1 'F[a]     F(1)'       "$LINENO"
runtest  36 'F[* a 2] F(18)'      "$LINENO"
runtest 256 'F[* a a] F(F(F(2)))' "$LINENO"

runtest 321 'F[* a  a] G[+ a a] - F(19) G(20)' "$LINENO"
runtest  42 'F[+ a  a] G[F(a)]       G(21)'    "$LINENO"
runtest  12 'F[+a 22]G[F(*a 23)] /G(24)F(25)'  "$LINENO"

runtest  53 'F[+ a b] F(26 27)'                     "$LINENO"
runtest 751 'F[* a b] G[+ a b] - F(28 29) G(30 31)' "$LINENO"

# Error
# 
# divided by 0
./lang '/ 18 0'     2>/dev/null && error "$LINENO"
./lang '/ 19 - 7 7' 2>/dev/null && error "$LINENO"

./lang a 2>/dev/null && error "accept digit only"

./lang '+ 1' 2>/dev/null && error "must not null"

./lang 2>/dev/null && error "no input program"

./lang 'F[' 2>/dev/null \
    && error "expect ']' before EOF"

./lang 'F[.] F(2]' 2>/dev/null \
    && error "')' expected: \"]]\""       

rm tmp.{0,1}

echo "Okay."

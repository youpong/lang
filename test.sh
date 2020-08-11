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

./lang a 2>/dev/null && error "Error: accept digit only"

rm tmp.{0,1}

echo "Okay."

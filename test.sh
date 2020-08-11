#!/bin/bash

LANG=C

function error() {
    echo "$@" >&2
    exit 1
}

cmp <(echo  0) <(./lang  0) || echo "Error: $LINENO"
cmp <(echo  1) <(./lang  1) || echo "Error: $LINENO"
cmp <(echo 42) <(./lang 42) || echo "Error: $LINENO"

cmp <(echo -e 1 2 3) <(./lang '1 2 3') || echo "Error: $LINENO"

./lang a && echo "Error: accept digit only"

echo "Ok." 

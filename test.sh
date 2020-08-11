#!/bin/bash

LANG=C

function error() {
    echo "$@" >&2
    exit 1
}

cmp <(echo 0) <(./lang 0) || echo "Error: $LINENO"
cmp <(echo 1) <(./lang 1) || echo "Error: $LINENO"

echo "Ok." 
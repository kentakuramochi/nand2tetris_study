#!/bin/bash

HASM_REF=../../../tools/Assembler.sh
HASM=./bin/asm

test_asm() {
    HACK=${1/.asm/.hack}

    ${HASM_REF} $1
    mv ${HACK} ./bin

    ${HASM} $1
    mv ${HACK} ./bin

    diff ./bin/$(basename ${HACK}) ${HACK}
}

# test for no label
test_asm ../add/Add.asm
test_asm ../max/MaxL.asm


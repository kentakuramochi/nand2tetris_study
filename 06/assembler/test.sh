#!/bin/bash

# assembler
HASM_REF=../../../tools/Assembler.sh
HASM_DIR=./bin
HASM=${HASM_DIR}/asm

test_asm() {
    SRC_DIR=$(dirname $1)
    HACK_BASE=$(basename ${1/.asm/.hack})

    HACK_REF=${HASM_DIR}/${HACK_BASE/.hack/_ref.hack}
    HACK=${HASM_DIR}/${HACK_BASE}

    # reference output
    ${HASM_REF} $1
    mv ${SRC_DIR}/${HACK_BASE} ${HACK_REF}

    # output
    ${HASM} $1
    mv ${SRC_DIR}/${HACK_BASE} ${HASM}

    # compare
    diff ${HACK_REF} ${HACK}
}

test_asm ../add/Add.asm
test_asm ../max/MaxL.asm


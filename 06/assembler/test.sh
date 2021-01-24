#!/bin/bash

# assembler
HASM_REF=../../../tools/Assembler.sh
HASM_DIR=./bin
HASM=${HASM_DIR}/Assembler

test_asm() {
    cp $1 ./

    HACK_SRC=$(basename $1)
    HACK_OUT=${HACK_SRC/.asm/.hack}
    HACK_OUT_REF=${HACK_OUT/.hack/_ref.hack}

    # reference output
    echo "reference output:"
    ${HASM_REF} ${HACK_SRC}
    mv ${HACK_OUT} ${HACK_OUT_REF}

    # output
    echo "output:"
    ${HASM} ${HACK_SRC}

    # compare
    diff ${HACK_OUT_REF} ${HACK_OUT}

    rm ${HACK_SRC}

    mv ${HACK_OUT} ${HACK_OUT_REF} ${HASM_DIR}
}

test_asm ../add/Add.asm
test_asm ../max/MaxL.asm
test_asm ../pong/PongL.asm
test_asm ../rect/RectL.asm

test_asm ../max/Max.asm
test_asm ../pong/Pong.asm
test_asm ../rect/Rect.asm

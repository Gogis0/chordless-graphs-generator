#!/bin/bash

# run a single .in, compare to corresponding .out
run () {
    echo -n "$1 ... "

    START=$(date +%s.%N)
    DIFF=$(./find_cycles < $1 | diff - ${1/in/out} )
    if [ "$DIFF" != "" ]; then
        echo -e "WRONG ANSWER:\n$DIFF "
    else
        echo -n "OK! "
    fi

    echo "time: $(echo "$(date +%s.%N) - $START" | bc) sec."
}

# if test case # is specified run it, else run all of them
if [ "$#" -eq 1 ]; then
    run $(echo "tests/$1.in")
else
    for input in tests/*.in; do
        run $input
    done
fi

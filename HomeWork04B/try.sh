#!/bin/sh

HW=HW04B
    
clang -pedantic -Wall -Werror -std=c99 -O3 -lm main.c -o $HW
echo "files compiled"
echo "launching file $HW"
./$HW


return 0
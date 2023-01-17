#!/bin/bash
pattern=$1
filename=$2


flags=("" "-l" "-e" "-c" "-n" "-i" "-v" "-h" "-s")

make
rm my_result.txt
rm real_result.txt
for (( i = 0; i <= 8; i++ ))
do
    n=$((i+1))
    echo "\n\nTEST № $n \n---------\n">>my_result.txt
    ./s21_grep ${flags[$i]} "$pattern" "$filename">>my_result.txt
    echo "\n\nTEST № $n \n---------\n">>real_result.txt
    grep ${flags[$i]} "$pattern" "$filename">>real_result.txt


    if diff my_result.txt real_result.txt
    then 
        echo ${flags[$i]}  SUCCESS
    else 
        echo ${flags[$i]}  FAIL
    fi 



done
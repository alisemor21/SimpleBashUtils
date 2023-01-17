#!/bin/bash

filename=$1

flags=("" "-b" "-e" "-n" "-s" "-t")

make

for (( i = 0; i <= 5; i++ ))
do
    n=$((i+1))
    echo "\n\nTEST № $n \n---------\n">>my_result.txt
    ./s21_cat ${flags[$i]} "$filename">>my_result.txt
    echo "\n\nTEST № $n \n---------\n">>real_result.txt
    cat ${flags[$i]} "$filename">>real_result.txt

    if diff my_result.txt real_result.txt
    then 
        echo ${flags[$i]}  SUCCESS
    else 
        echo ${flags[$i]}  FAIL
    fi 
done


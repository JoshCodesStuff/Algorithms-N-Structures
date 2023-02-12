#! /bin/bash

for test in test/test_*.txt;
do :
    tmp="$test";
    tmp="${tmp#*_}";
    tmp="${tmp%.*}";

    output="test/out_$tmp.txt";
    compare="test/comp_$tmp.txt"

    printf "Executing for $test...\n";

    # test the compilation
    printf "\nTesting:\n$firstline"
    read -r firstline < $test;
    echo "$firstline" | ./avl.out > $output;

    if [ "$?" != "0" ];
    then
        printf "$test failed!\n";
        exit 1;
    fi

    printf "\nResult of $test:\n";
    read -r out $output;
    read -r driver $compare;

    echo "$out"
    echo "$driver"

    # if [ $out != $driver ];
    # then
    #     echo -e "\e[1;31;101mTEST FAILED\e[0m"
    # else
    #     echo -e "\e[1;32;102mTEST PASSED\e[0m"
    # fi;
done
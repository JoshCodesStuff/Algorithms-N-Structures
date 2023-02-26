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
done
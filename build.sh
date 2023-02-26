#! /bin/bash

for source in *.cpp;
do :
  printf "Compiling $source...\n";
  g++ -std=c++14 -Wall -pedantic "./$source" -o "${source%.*}.out";
  if [ "$?" != "0" ];
  then
    printf "Compilation failed!\n";
    exit 1;
  fi
  printf "\n";
done
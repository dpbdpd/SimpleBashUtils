#!/bin/bash
SUCCESS=0
FAIL=0
COUNTER=0


flags=(
    "v"
    "c"
    "l"
    "n"
   )

tests=(
"s test_files/test_0_grep.txt FLAGS"
"for s21_grep.c s21_grep.h Makefile FLAGS"
"for s21_grep.c FLAGS"
"-e for -e ^int s21_grep.c s21_grep.h Makefile FLAGS"
"-e for -e ^int s21_grep.c FLAGS"
"-e regex -e ^print s21_grep.c FLAGS"
"-e while -e void s21_grep.c Makefile FLAGS"
"-e intel -e int FLAGS test_files/test_7_grep.txt"
"-e int -e intel FLAGS test_files/test_7_grep.txt"
)

manual=(
"-e ^\} test_files/test_1_grep.txt"
"-c ^int test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-e ^int test_files/test_1_grep.txt"
"-e INT test_files/test_5_grep.txt"
"-echar test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-e = -e out test_files/test_5_grep.txt"
"-v int test_files/test_5_grep.txt"
"-i int test_files/test_5_grep.txt"
"-c aboba test_files/test_1_grep.txt test_files/test_5_grep.txt"
"test_files/test_1_grep.txt -e ank"
"-e ) test_files/test_5_grep.txt"
"-l for test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-e int test_files/test_4_grep.txt"
"-e = -e out test_files/test_5_grep.txt"
"-e ing -e as -e the -e not -e is test_files/test_6_grep.txt"
"-l for no_file.txt test_files/test_2_grep.txt"
"-e int -i no_file.txt s21_grep.c no_file2.txt s21_grep.h"
)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    ./s21_grep $param > s21_grep.log
    grep $param > grep.log
    DIFF="$(diff -s s21_grep.log grep.log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files s21_grep.log and grep.log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm s21_grep.log grep.log
}

for i in "${manual[@]}"
do
    var="-"
    run_test "$i"
done

printf "\n"
echo "======================="
echo "1 PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test "$i"
    done
done

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"

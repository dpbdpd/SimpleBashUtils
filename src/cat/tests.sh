#!/bin/bash

count=0
fail=0
success=0
DIFF=""

flags=(
    "b"
    "e"
    "n"
    "s"
    "t"
    "v"
)

tests=(
    test_files/test_1_cat.txt
    test_files/test_2_cat.txt
    test_files/test_3_cat.txt
    test_files/test_4_cat.txt
    test_files/test_5_cat.txt
    test_files/test_case_cat.txt
)


rez(){
    ((count++))
    ./s21_cat $var $str > s21_cat.log
    cat $var $str  > cat.log
    DIFF="$(diff -s s21_cat.log cat.log)"
    if [ "$DIFF" == "Files s21_cat.log and cat.log are identical" ]
    then 
    ((success++))
    echo "$count" - Success $var $str
    else 
    ((fail++))
    echo "$count" - fail $var $str

    fi
    rm s21_cat.log cat.log

}

for var1 in "${flags[@]}"
do
    for str in "${tests[@]}"
    do 
        var="-$var1"
        rez "$str"
    done
done

for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do 
        for j in "${tests[@]}"
        do
        var="-$var1"
        str="$i $j"
        rez "$str"
        done
    done
done


echo "ALL: $count"
echo "FAILED: $fail"
echo "SUCCESSFUL: $success"
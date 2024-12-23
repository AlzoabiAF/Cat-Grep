#!/bin/bash

SUCCESS=0
FAIL=0
COUNT=0

declare -a testFile=(
"VAR test1.txt"
"VAR test2.txt"
"VAR test3.txt"
"VAR test4.txt"
"VAR test2.txt test4.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    eval "./s21_cat $t > test_s21_cat.log 2>&1"
    eval "cat $t > test_sys_cat.log 2>&1"
    (( COUNT++ ))
    if [ "$(diff -s test_s21_cat.log test_sys_cat.log)" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
        (( SUCCESS++ ))
        echo "$COUNT: OK"
    else
        (( FAIL++ ))
        echo "$COUNT: FAIL"
    fi
    rm test_s21_cat.log test_sys_cat.log
}


for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${testFile[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done


echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
echo "ALL: $COUNT"
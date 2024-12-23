#!/bin/bash

SUCCESS=0
FAIL=0
COUNT=0
DIFF=""

declare -a multy_testing=( 
"VAR s -o test3.txt"
"VAR s test1.txt"
"test127.txt s VAR"
"D VAR test1.txt"
"S VAR test1.txt test2.txt test1.txt"
"-e s VAR -o test3.txt"
"-e ^int VAR test1.txt test2.txt test1.txt"
"-f VAR pattern_file.txt test3.txt test2.txt test1.txt"
"-f pattern_file.txt test3.txt test2.txt test6.txt"
)

testing()
{   
    t=$(echo $@ | sed "s/VAR/$var/")
    eval "./s21_grep $t > test_s21_grep.log 2>&1" 
    eval "grep $t > test_sys_grep.log 2>&1"
    DIFF=$(diff -s test_s21_grep.log test_sys_grep.log)
    (( COUNT++ ))
    if [ "$DIFF" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "TEST $COUNT: OK"
    else
      (( FAIL++ ))
      echo "TEST $COUNT: FAIL"
      eval "echo $FAIL $t >> log.log 2>&1"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for var1 in e i v c l n h s o f 
do
  for i in "${multy_testing[@]}"
  do
    var="-$var1"
    testing $i
  done
done

for var1 in e i v c l n h s f o
do
  for var2 in e i v c l n h s f
  do
    if [[ "$var1$var2" == "of" || "$var1$var2" == "fo" ]]; then
      continue
    fi
    for i in "${multy_testing[@]}"
    do
      var="-$var1$var2"
      testing "$i"
    done
  done
done


for var1 in i v c l n h s o
do
  for var2 in i v c l n h s o
  do
    for var3 in i v c l n h s o
    do
      for i in "${multy_testing[@]}"
      do
        var="-$var1$var2$var3"
        testing $i
      done   
    done
  done
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
echo "ALL: $COUNT"
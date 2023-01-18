#!/bin/bash
correct=0
incorrect=0
export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH
for FILE in tests/*.in; do ./bin/main < $FILE > ${FILE//.in/.out} ; if diff -w ${FILE//.in/.out} ${FILE//.in/.expected} ; then echo $FILE PASSED ; ((correct+=1)) ; else echo $FILE FAILED; ((incorrect+=1)) ;  fi ; done

echo ""
echo "Test cases passed: $correct"

echo "Test cases failed: $incorrect"
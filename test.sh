g++ -std=c++17 test.cpp
./a.out > result.txt
if `cmp correct.txt result.txt` ; then echo "ok" ; rm result.txt ; else echo "A test didn't pass" ; fi
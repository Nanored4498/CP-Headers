python3 expand_headers.py test.cpp test2.cpp
g++ -std=c++17 test2.cpp
./a.out > result.txt
if `cmp correct.txt result.txt` ; then echo "ok" ; rm result.txt ; else echo "A test didn't pass" ; fi
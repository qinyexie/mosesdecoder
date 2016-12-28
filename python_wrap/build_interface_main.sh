g++ mymain.cpp -I ../ -I ../opt/include -L ./lib -L ../opt/lib -lmoses -lboost_thread -lboost_system -std=c++11 -DMAX_NUM_FACTORS=4 -DWITH_THREADS
cd ./test/sample-models/
../../a.out -f phrase-model/moses.in

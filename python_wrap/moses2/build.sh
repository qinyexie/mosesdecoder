rm *.out *.o core.*

rm -rf ../../contrib/moses2/bin
rm -rf ../lib
cd ../..
./compile.sh
cd python_wrap/moses2

g++ Interface.cpp mymain.cpp -I ../../opt/include -I ../../ -L ../../opt/lib -L ../lib -lmoses2_lib -lboost_thread -lboost_system -DMAX_NUM_FACTORS=4 -DWITH_THREADS -g -o main_moses_file.out

# g++ Interface.cpp mymain2.cpp -I ../../ -I ../../opt/include -L ../../opt/lib -L ../lib -lmoses2_lib -lboost_thread -lboost_system -DMAX_NUM_FACTORS=4 -DWITH_THREADS -o main_moses_arg.out

g++ PythonInterface.cpp -o translate.so -shared -I /work/pybind11/include -I ../ -I ../opt/include -L ./lib -L ../opt/lib -lmoses -lboost_thread -lboost_system -lpthread -std=c++11 -fPIC -DMAX_NUM_FACTORS=4 -DWITH_THREADS `python-config --cflags --ldflags`
# g++ -shared -I /work/pybind11/include -I ../ -L ./lib -L ../opt/lib -lmoses -lboost_thread -std=c++11 -DMAX_NUM_FACTORS=4 -DWITH_THREADS `python-config --cflags --ldflags` PythonInterface.cpp -o translate.so

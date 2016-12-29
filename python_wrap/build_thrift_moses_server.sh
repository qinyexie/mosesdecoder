#!/bin/bash
c++ CppServer.cpp gen-cpp/SMT.cpp gen-cpp/tutorial_cpp_types.cpp -I gen-cpp/ -I ../ -I ../opt/include -L ./lib -L ../opt/lib -lmoses -lboost_thread -lboost_system -lthrift -DMAX_NUM_FACTORS=4 -DWITH_THREADS

#include"Interface.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string& moses_init_path = string(argv[1]);
    }
    else
    {
        return -1
    }
    translation = Moses2::TranslationInterface(moses_init_path);
    translation.translate();
}
#include"Interface.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        return -1;
    }
    const string& moses_init_path = string(argv[1]);

    Moses2::TranslationInterface translation = Moses2::TranslationInterface(moses_init_path);
    translation.translate();
}
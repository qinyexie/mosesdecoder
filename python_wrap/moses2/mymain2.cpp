#include"Interface.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Moses2::TranslationInterface translation = Moses2::TranslationInterface(argc, argv);
    translation.translate();
}
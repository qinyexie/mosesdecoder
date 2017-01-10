#include"Interface.h"
#include<iostream>
#include "../../contrib/moses2/FF/FeatureRegistry.h"
using namespace std;

int main(int argc, char* argv[])
{
/*
    if(argc < 2)
    {
        return -1;
    }
*/
    // const string& moses_init_path = string(argv[1]);
    string s = "phrase-model/moses.ini";
    const string& moses_init_path = s;

    Moses2::TranslationInterface translation = Moses2::TranslationInterface(moses_init_path);
    translation.translate();
}
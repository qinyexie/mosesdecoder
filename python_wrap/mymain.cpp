#include "moses/ExportInterface.h"
#include "util/string_stream.hh"
#include <iostream>

int main(int argc, char const** argv)
{
    std::string s = "phrase-model/moses.ini";
    SimpleTranslationInterface trans = SimpleTranslationInterface(s);
    std::string in = "das ist ein kleines haus";
    std::string r = trans.translate(in);
    std::cout << r << std::endl;
}
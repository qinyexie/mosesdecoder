#pragma once
#include <iostream>

namespace Moses2
{
    class Parameter;
    class System;
    class ThreadPool;

    class TranslationInterface
    {
    public:
        TranslationInterface(const std::string &mosesIni);
        ~TranslationInterface();
        std::string translate(const std::string &input);
        Moses::Parameter& getParameters()
        {
            return m_params;
        };
    private:
        SimpleTranslationInterface();
        Parameter *m_params;
        System *m_system;
        ThreadPool *m_pool;
    };
}

std::istream &GetInputStream(Moses2::Parameter &params);
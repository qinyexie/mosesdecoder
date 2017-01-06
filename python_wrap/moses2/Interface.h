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
        static void DestroyFeatureFunctionStatic();
        TranslationInterface(const std::string &mosesIni);
        ~TranslationInterface();
        std::string translate(const std::string &input);
        Moses::StaticData& getStaticData();
        Moses::Parameter& getParameters()
        {
            return m_params;
        }
    private:
        SimpleTranslationInterface();
        Parameter m_params;
        const Moses::StaticData& m_staticData;
        
    }
}

std::istream &GetInputStream(Moses2::Parameter &params);
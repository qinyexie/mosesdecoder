#pragma once
#include <iostream>
#include "../../contrib/moses2/System.h"
#include "../../contrib/moses2/legacy/Parameter.h"
#include "../../contrib/moses2/System.h"


namespace Moses2
{
    // class Parameter;
    class System;
    class ThreadPool;

    class TranslationInterface
    {
    public:
        TranslationInterface(const std::string& mosesInit);
        ~TranslationInterface(){};
        // std::string translate(const std::string &input);
        void translate();
        Parameter& getParameters()
        {
            return m_params;
        };
    private:
        TranslationInterface();
        Parameter m_params;
        boost::shared_ptr<System>pm_system;
        boost::shared_ptr<ThreadPool>pm_pool;
        int init_state;
    };
}

std::istream &GetInputStream(Moses2::Parameter &params);
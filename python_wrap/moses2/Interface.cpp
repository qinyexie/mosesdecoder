#include <iostream>
#include <memory>
#include <boost/pool/pool_alloc.hpp>
#include "../../contrib/moses2/System.h"
#include "../../contrib/moses2/Phrase.h"
#include "../../contrib/moses2/TranslationTask.h"
#include "../../contrib/moses2/MemPoolAllocator.h"
#include "../../contrib/moses2/server/Server.h"
#include "../../contrib/moses2/legacy/InputFileStream.h"
#include "../../contrib/moses2/legacy/Parameter.h"
#include "../../contrib/moses2/legacy/ThreadPool.h"
#include "../../contrib/moses2/legacy/Timer.h"
#include "../../contrib/moses2/legacy/Util2.h"
#include "../../contrib/moses2/util/usage.hh"

using namespace std;

namespace Moses2
{
    istream &GetInputStream(Moses2::Parameter &params)
    {
        const Moses2::PARAM_VEC *vec = params.GetParam("input-file");
        if (vec && vec->size()) {
            Moses2::InputFileStream *stream = new Moses2::InputFileStream(vec->at(0));
            return *stream;
        }
        else {
            return cin;
        }
    }

    TranslationInterface::TranslationInterface(string &moses_init)
    {
        cerr << "Starting..." << endl;

        Moses2::Timer timer;
        timer.start();

        if (!m_params.LoadParam(&moses_init)) {
            return EXIT_FAILURE;
        }

        m_system = System(m_params);
        timer.check("Loaded");

        if (m_params.GetParam("show-weights")) {
            return EXIT_SUCCESS;
        }

        cerr << "system.numThreads=" << system.options.server.numThreads << endl;
        m_pool = Moses2::ThreadPool pool(system.options.server.numThreads, system.cpuAffinityOffset, system.cpuAffinityOffsetIncr);
        cerr << "CREATED POOL" << endl
    }

    TranslationInterface::~TranslationInterface(){}

    void TranslationInterface::translate()
    {
        istream &inStream = GetInputStream(m_params);

        long translationId = 0;
        string line;
        while (getline(inStream, line)) {
            //cerr << "line=" << line << endl;
            std::shared_ptr<Moses2::TranslationTask> task(new Moses2::TranslationTask(system, line, translationId));

            //cerr << "START pool.Submit()" << endl;
            pool.Submit(task);
            //task->Run();
            ++translationId;
        }

        pool.Stop(true);

        if (&inStream != &cin) {
            delete &inStream;
        }

        //util::PrintUsage(std::cerr);

    }
}
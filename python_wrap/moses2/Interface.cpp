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
#include "../../util/usage.hh"
#include "Interface.h"

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

    TranslationInterface::TranslationInterface(const string& mosesInit)
    {
        cerr << "Starting..." << endl;
        init_state = -1;

        Moses2::Timer timer;
        timer.start();

        if (!m_params.LoadParam(mosesInit)) {
            init_state = EXIT_FAILURE;
        }

        pm_system.reset(new System(m_params));
        timer.check("Loaded");

        if (m_params.GetParam("show-weights")) {
            init_state = EXIT_SUCCESS;
        }

        cerr << "system.numThreads=" << pm_system->options.server.numThreads << endl;
        pm_pool.reset(new Moses2::ThreadPool(pm_system->options.server.numThreads, pm_system->cpuAffinityOffset, pm_system->cpuAffinityOffsetIncr));
        init_state = 0;
        cerr << "CREATED POOL" << endl;
    }

    void TranslationInterface::translate()
    {
        istream &inStream = GetInputStream(m_params);

        long translationId = 0;
        string line;
        while (getline(inStream, line)) {
            //cerr << "line=" << line << endl;
            boost::shared_ptr<Moses2::TranslationTask> task(new Moses2::TranslationTask(*pm_system, line, translationId));

            //cerr << "START pool.Submit()" << endl;
            pm_pool->Submit(task);
            //task->Run();
            ++translationId;
        }

        pm_pool->Stop(true);

        if (&inStream != &cin) {
            delete &inStream;
        }

        //util::PrintUsage(std::cerr);

    }
}
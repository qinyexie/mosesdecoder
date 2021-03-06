/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include <boost/make_shared.hpp>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../gen-cpp/SMT.h"

#include "moses/ExportInterface.h"
#include "util/string_stream.hh"
#include <iostream>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace tutorial;

static SimpleTranslationInterface *ptrans = NULL;

class SMTHandler : public SMTIf {
public:
  SMTHandler(){}

  int32_t init()
  {
    if(ptrans == NULL)
      return 1;
    else
      return 0;
  }
  
  void translate(Work& _return, const int32_t id, const string& sent)
  {
    string r = ptrans->translate(sent);
    _return.id = id;
    _return.input_sent = sent;
    _return.translate_ret = r;
  }

protected:
  // map<int32_t, string> log;
};

/*
  SMTIfFactory is code generated.
  SMTCloneFactory is useful for getting access to the server side of the
  transport.  It is also useful for making per-connection state.  Without this
  CloneFactory, all connections will end up sharing the same handler instance.
*/
class SMTCloneFactory : virtual public SMTIfFactory {
public:
  virtual ~SMTCloneFactory() {}
  virtual SMTIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo)
  {
    boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
    cout << "Incoming connection\n";
    cout << "\tSocketInfo: "  << sock->getSocketInfo() << "\n";
    cout << "\tPeerHost: "    << sock->getPeerHost() << "\n";
    cout << "\tPeerAddress: " << sock->getPeerAddress() << "\n";
    cout << "\tPeerPort: "    << sock->getPeerPort() << "\n";
    return new SMTHandler;
  }

  virtual void releaseHandler( SMTIf* handler) {
    delete handler;
  }
};

int main(int argc, char* argv[]) {

  if (argc < 2)
    {
      cout << "args 1: model file\nargs 2: port(defaut 8761)\n";
      return -1;
    }
  else
    {
      string s = string(argv[1]);
      cout << "init moses by config " << s << endl;
      ptrans = new SimpleTranslationInterface(s);
    }

  int port = 8761;
  if (argc == 3)
    {
      port = atoi(argv[2]);
    }

  TThreadedServer server(
			 boost::make_shared<SMTProcessorFactory>(boost::make_shared<SMTCloneFactory>()),
			 boost::make_shared<TServerSocket>(port), //port
			 boost::make_shared<TBufferedTransportFactory>(),
			 boost::make_shared<TBinaryProtocolFactory>());

  /*
  // if you don't need per-connection state, do the following instead
  TThreadedServer server(
  boost::make_shared<SMTProcessor>(boost::make_shared<SMTHandler>()),
  boost::make_shared<TServerSocket>(9090), //port
  boost::make_shared<TBufferedTransportFactory>(),
  boost::make_shared<TBinaryProtocolFactory>());
  */

  /**
   * Here are some alternate server types...

   // This server only allows one connection at a time, but spawns no threads
   TSimpleServer server(
   boost::make_shared<SMTProcessor>(boost::make_shared<SMTHandler>()),
   boost::make_shared<TServerSocket>(9090),
   boost::make_shared<TBufferedTransportFactory>(),
   boost::make_shared<TBinaryProtocolFactory>());

   const int workerCount = 4;

   boost::shared_ptr<ThreadManager> threadManager =
   ThreadManager::newSimpleThreadManager(workerCount);
   threadManager->threadFactory(
   boost::make_shared<PlatformThreadFactory>());
   threadManager->start();

   // This server allows "workerCount" connection at a time, and reuses threads
   TThreadPoolServer server(
   boost::make_shared<SMTProcessorFactory>(boost::make_shared<SMTCloneFactory>()),
   boost::make_shared<TServerSocket>(9090),
   boost::make_shared<TBufferedTransportFactory>(),
   boost::make_shared<TBinaryProtocolFactory>(),
   threadManager);
  */

  cout << "Starting the server..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}

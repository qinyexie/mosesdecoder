#!/usr/bin/env python
# -*- coding:utf-8 -*-
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements. See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership. The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the
# specific language governing permissions and limitations
# under the License.
#

import sys
sys.path.append('gen-py')

from tutorial_cpp import SMT
from tutorial_cpp.ttypes import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
import threading
from multiprocessing import process

def moses_python_warp(s):
  try:
    # Make socket
    transport = TSocket.TSocket('localhost', 9090)
    # Buffering is critical. Raw sockets are very slow
    transport = TTransport.TBufferedTransport(transport)
    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    # Create a client to use the protocol encoder
    client = SMT.Client(protocol)
    # Connect!
    transport.open()

    # client.init()
    # print 'init()'
    sid = hash(s) / 9188098211
    work = client.translate(sid, s)
    assert sid == work.id

    transport.close()

    return work.translate_ret

  except Thrift.TException, tx:
    print '%s' % (tx.message)

if __name__ == '__main__':
  import time
  ts = time.time()
  for i in range(100):
    t1 = threading.Thread(target=moses_python_warp, args=('蓝色 小 苹果',))
    t2 = threading.Thread(target=moses_python_warp, args=('讲 个 故事 吧',))
    t3 = threading.Thread(target=moses_python_warp, args=('现在 速度 柑橘 好 慢',))
    t1.start()
    t2.start()
    t3.start()
    t1.join()
    t2.join()
    t3.join()
  te = time.time()
  print te - ts

  ts = time.time()
  for i in range(100):
    p1 = process.Process(target=moses_python_warp, args=('蓝色 小 苹果',))
    p2 = process.Process(target=moses_python_warp, args=('讲 个 故事 吧',))
    p3 = process.Process(target=moses_python_warp, args=('现在 速度 柑橘 好 慢',))
    p1.start()
    p2.start()
    p3.start()
    p1.join()
    p2.join()
    p3.join()
  te = time.time()
  print te - ts
  

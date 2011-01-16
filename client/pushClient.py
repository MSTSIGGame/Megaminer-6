#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-

import rpyc
import sys

if __name__ == '__main__':
  host = sys.argv[1]
  binary = file(sys.argv[2], 'rb')
  name = sys.argv[3]
  password = sys.argv[4]
  
  server = rpyc.connect(host,18862)
  if server.root.update(name, password, binary.read()):
    print "Push successful!"
  else:
    print "Push failed. :("
  
  server.close()
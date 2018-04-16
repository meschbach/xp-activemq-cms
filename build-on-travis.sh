#!/usr/bin/env bash

#
# Install Apache CMS
#
curl http://mirror.cogentco.com/pub/apache/activemq/activemq-cpp/3.9.4/activemq-cpp-library-3.9.4-src.tar.bz2 -o activemq-cpp-library.tar.bz2
tar xf activemq-cpp-library.tar.bz2
cd activemq-cpp-library*
./configure --prefix=$PWD/../amq-cms
make LDFLAGS="-pthread `./amq-cms/bin/activemqcpp-config --libs`" CXXFLAGS="`./amq-cms/bin/activemqcpp-config --cflags` -std=c++17 -Wno-deprecated-declarations -pthread"
echo "Completed build."
ls -lah
#!/bin/sh
rm -rf cmakebuild
CMaker project:maraton compiler:clang++ head:*.h src:*.cpp,*.c src:*.cc,*.cpp,*.hpp lib:/usr/lib/libuv.a,lib/libmaraton.a,/usr/libprotobuf.a flag:-std=c++11-pthread out:lib 
cd cmakebuild
cmake ./
make

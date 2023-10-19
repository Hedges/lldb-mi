@echo off
set lib_lldb=../llvm/build/$(Configuration)/lib/liblldb
c:\Tools\cmake\bin\cmake.exe -B build -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=..\llvm\build

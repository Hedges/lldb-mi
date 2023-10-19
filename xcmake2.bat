@echo off
set CC=C:\msys64\ucrt64\bin\clang.exe
set CXX=C:\msys64\ucrt64\bin\clang++.exe
set lib_lldb=../llvm17/build/$(Configuration)/lib/liblldb
c:\Tools\cmake\bin\cmake.exe -B build2 -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=..\llvm17\build
rem  -Wl,-start-group C:/Projects/_3rdParty/Hedges/llvm17/build/Release/lib/libclang-cpp.lib C:/Projects/_3rdParty/Hedges/llvm17/build/Release/lib/liblldb.lib C:/Projects/_3rdParty/Hedges/llvm17/build/Release/lib/libLLVM.lib -lpsapi -lshell32 -lole32 -luuid -ladvapi32 -ldelayimp -delayload:shell32.dll -delayload:ole32.dll C:/Projects/_3rdParty/Hedges/llvm17/build/Release/lib/LLVMDemangle.lib -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -Wl,-end-group

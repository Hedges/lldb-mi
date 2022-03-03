//===-- MIUtilDebug.cpp -----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// Third party headers:
#ifdef _WIN32
#include "Platform.h"
#endif

// In-house headers:
#include "MICmnLog.h"
#include "MIDriver.h"
#include "MIUtilDebug.h"

//++
// Details: CMIUtilDebug constructor.
// Type:    Method.
// Args:    None.
// Return:  None.
// Throws:  None.
//--
CMIUtilDebug::CMIUtilDebug() {}

//++
// Details: CMIUtilDebug destructor.
// Type:    Method.
// Args:    None.
// Return:  None.
// Throws:  None.
//--
CMIUtilDebug::~CMIUtilDebug() {}

//++
// Details: Temporarily stall the process/application to give the programmer the
//          opportunity to attach a debugger. How to use: Put a break in the
//          programmer
//          where you want to visit, run the application then attach your
//          debugger to the
//          application. Hit the debugger's pause button and the debugger should
//          should
//          show this loop. Change the i variable value to break out of the loop
//          and
//          visit your break point.
// Type:    Static method.
// Args:    None.
// Return:  None.
// Throws:  None.
//--
void CMIUtilDebug::WaitForDbgAttachInfinteLoop() {
  MIuint i = 0;
  while (i == 0) {
    const std::chrono::milliseconds time(100);
    std::this_thread::sleep_for(time);
  }
}

//++
// Details: Return path to SDK Root containing symbols used for debugging.
// Type:    Static method.
// Args:    None.
// Return:  Path to SDK Root.
// Throws:  None.
//--
const char *CMIUtilDebug::GetSDKRootPath()
{
    static char szSDKRootPath[MAX_PATH];
    char *pszEnv = getenv("APPLESDKROOT");
    if(!pszEnv)
    {
        pszEnv = getenv("APPLESDK");
        if(!pszEnv)
        {
            pszEnv = (char *)"C:\\AppleSDK";
        }
    }
    strcpy(szSDKRootPath, pszEnv);
    return szSDKRootPath;
}

CMIUtilString CMIUtilDebug::m_strRemoteExe;

//++
// Details: Sets path to executable installed on remote device.
// Type:    Static method.
// Args:    None.
// Return:  None.
// Throws:  None.
//--
void CMIUtilDebug::SetRemoteExePath(const char *szRemoteExe)
{
    if(szRemoteExe[0] != '@')
    {
        m_strRemoteExe = szRemoteExe;
    }
    else
    {
        FILE *f = fopen(&szRemoteExe[1], "rb");
        if(f)
        {
            char buff[MAX_PATH];
            fgets(buff, sizeof(buff), f);
            //https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
            buff[strcspn(buff, "\r\n")] = 0;
            m_strRemoteExe = buff;
            fclose(f);
        }
    }
}

//++
// Details: Return path to executable installed on remote device.
// Type:    Static method.
// Args:    None.
// Return:  Path to executable installed on remote device.
// Throws:  None.
//--
const char *CMIUtilDebug::GetRemoteExePath()
{
    return m_strRemoteExe.c_str();
}

// Instantiations:
CMICmnLog &CMIUtilDebugFnTrace::ms_rLog = CMICmnLog::Instance();
MIuint CMIUtilDebugFnTrace::ms_fnDepthCnt = 0;

//++
// Details: CMIUtilDebugFnTrace constructor.
// Type:    Method.
// Args:    vFnName - (R) The text to insert into the log.
// Return:  None.
// Throws:  None.
//--
CMIUtilDebugFnTrace::CMIUtilDebugFnTrace(const CMIUtilString &vFnName)
    : m_strFnName(vFnName) {
  const CMIUtilString txt(
      CMIUtilString::Format("%d>%s", ++ms_fnDepthCnt, m_strFnName.c_str()));
  ms_rLog.Write(txt, CMICmnLog::eLogVerbosity_FnTrace);
}

//++
// Details: CMIUtilDebugFnTrace destructor.
// Type:    Method.
// Args:    None.
// Return:  None.
// Throws:  None.
//--
CMIUtilDebugFnTrace::~CMIUtilDebugFnTrace() {
  const CMIUtilString txt(
      CMIUtilString::Format("%d<%s", ms_fnDepthCnt--, m_strFnName.c_str()));
  ms_rLog.Write(txt, CMICmnLog::eLogVerbosity_FnTrace);
}

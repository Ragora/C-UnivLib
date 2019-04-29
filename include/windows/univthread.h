/**
 *  @brief Definitions for a universal thread on Windows.
 */

#ifndef _INCLUDE_UNIVTHREAD_WINDOWS_H_

//! All platforms should set this variable so we know we've included a platform specfic thread definition.
#define _INCLUDE_UNIVTHREAD_PLATFORM_H_

#define _INCLUDE_UNIVTHREAD_WINDOWS_H_

#include <windows.h>

//! A universal thread on Windows.
struct UnivThread
{
    //! The thread object.
    HANDLE thread;

    //! The start routine that was used for this thread.
    ThreadStartRoutine startRoutine;

    //! The return value.
    void *result;
};

#endif

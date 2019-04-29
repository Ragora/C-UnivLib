/**
 *  @brief Definitions for a Universal thread on Linux.
 */

#ifndef _INCLUDE_UNIVTHREAD_LINUX_H_

    //! All platforms should set this variable so we know we've included a platform specfic thread definition.
    #define _INCLUDE_UNIVTHREAD_PLATFORM_H_
    #define _INCLUDE_UNIVTHREAD_LINUX_H_

    #include <pthread.h>

    #include <all/univthread.h>

    //! A universal thread on Linux.
    struct UnivThread
    {
        //! The thread object.
        pthread_t thread;

        //! Thread attributes.
        pthread_attr_t attributes;

        //! The start routine that was used for this thread.
        ThreadStartRoutine startRoutine;

        //! The thread parameter.
        void *parameter;
    };
#endif

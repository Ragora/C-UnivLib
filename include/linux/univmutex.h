/**
 *  @brief Linux definitions of a universal mutex.
 */

#ifndef _INCLUDE_UNIVMUTEX_LINUX_H_
    #include <pthread.h>

    //! All platforms should set this variable so we know we've included a platform specfic mutex definition.
    #define _INCLUDE_UNIVMUTEX_PLATFORM_H_

    #define _INCLUDE_UNIVMUTEX_LINUX_H_

    //! Linux specific definition of the UnivMutex.
    struct UnivMutex
    {
        //! The internal pthread mutex.
        pthread_mutex_t internal;
    };

#endif

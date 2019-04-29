/**
 *  @brief Main include file for univthread.
 */

#ifndef _INCLUDE_UNIVMUTEX_ALL_H_
    #define _INCLUDE_UNIVMUTEX_ALL_H_

    // If compiling with C++, wrap our includes with extern C.
    #ifdef __cplusplus
        extern "C"
        {
    #endif

    #ifndef _INCLUDE_UNIVMUTEX_PLATFORM_H_
        //! When being included normally, this is a forward declaration of UnivMutex.
        struct UnivMutex;
    #endif

    /**
     *  @brief Creates a new UnivMutex instance, returning a pointer to the mutex.
     *  @return The allocated mutex instance.
     */
    struct UnivMutex* univmutex_create(void);

    /**
     *  @brief Acquires a lock on the mutex.
     *  @param mutex The mutex to lock.
     */
    void univmutex_lock(struct UnivMutex *mutex);

    /**
     *  @brief Releases a lock on the mutex.
     *  @param mutex The mutex to unlock.
     */
    void univmutex_unlock(struct UnivMutex *mutex);

    /**
     *  @brief Destroys the mutex.
     *  @param mutex The mutex to destroy.
     */
    void univmutex_destroy(struct UnivMutex *mutex);

    #ifdef __cplusplus
        }
    #endif
#endif

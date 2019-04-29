/**
 *  @brief Main include file for univthread.
 */

#ifndef _INCLUDE_UNIVTHREAD_ALL_H_
    #define _INCLUDE_UNIVTHREAD_ALL_H_

    // If compiling with C++, wrap our includes with extern C.
    #ifdef __cplusplus
        extern "C"
        {
    #endif

    //! A generic definition for a thread start routine.
    typedef void*(*ThreadStartRoutine)(void*);

    #ifndef _INCLUDE_UNIVTHREAD_PLATFORM_H_
        //! When being included normally, this is a forward declaration of UnivThread.
        struct UnivThread;
    #endif

    /**
     *  @brief Creates a new UnivThread instance, returning a pointer to the thread.
     *  @param startRoutine The routine to run inside of this thread.
     *  @param parameter The parameter to pass into the thread.
     *  @return The allocated thread instance.
     */
    struct UnivThread* univthread_create(ThreadStartRoutine startRoutine, void *parameter);

    /**
     *  @brief Joins on the UnivThread, blocking execution until it has returned.
     *  @param thread The thread to wait for.
     *  @return The return result of the thread.
     */
    void* univthread_join(struct UnivThread *thread);

    /**
     *  @brief Asks the UnivThread to cancel.
     *  @param thread The thread to send a cancel signal to.
     */
    void univthread_cancel(struct UnivThread *thread);

    /**
     *  @brief Destroys the UnivThread handle.
     *  @param thread The thread to destroy.
     *  @note The thread handle after calling this will no longer be valid.
     */
    void univthread_destroy(struct UnivThread *thread);

    /**
     *  @brief Suspends the UnivThread handle.
     *  @param thread The thread to suspend.
     */
    void univthread_suspend(struct UnivThread *thread);

    /**
     *  @brief Resumes the UnivThread handle.
     *  @param thread The thread to resume.
     */
    void univthread_resume(struct UnivThread *thread);


    #ifdef __cplusplus
        }
    #endif
#endif

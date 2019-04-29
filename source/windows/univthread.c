/**
 *  @brief Source implementation of UnivThread on Windows.
 */

#include <stdlib.h>

#include <windows/univthread.h>

//! A structure representing parameters to be passed to the thread.
struct InternalThreadParameters
{
    //! The parameter to be passed to the real thread routine.
    void *parameter;

    //! The thread object.
    UnivThread *thread;
};

/**
 *  @brief The internal thread function for Windows. This is used because on Windows, the thread returns are handled differently than on Linux with pthreads.
 */
DWORD WINAPI InternalThreadFunction(void* data)
{
    struct InternalThreadParameters *threadParameters = (struct InternalThreadParameters*)data;

    // Copy thread parameters to the stack so the thread parameters pointer can go invalid without issue.
    void *parameter = threadParameters->parameter;
    UnivThread *thread = threadParameters->thread;

    thread->result = thread->startRoutine(parameter);

    // FIXME: Is it proper to just cast the return like this?
    return (DWORD)thread->result;
}

struct UnivThread* univthread_create(ThreadStartRoutine startRoutine, void *parameter)
{
    // FIXME: Does Windows prefer something else for allocation here?
    struct UnivThread *result = calloc(1, sizeof(struct UnivThread));
    result->startRoutine = startRoutine;

    // Setup the start parameters
    // FIXME: Wait for the thread to get past init before continuing?
    InternalThreadParameters internalParameters = {
        .thread = result,
        .parameter = parameter
    };

    LPVOID threadParameter = (LPVOID)&internalParameters;
    result->thread = CreateThread(NULL, 0, InternalThreadFunction, threadParameter, 0, NULL);

    if (!result->thread)
    {
        free(result);
        return NULL;
    }

    return result;
}

void* univthread_join(struct UnivThread *thread)
{
    // Wait indefinitely for the thread to exit.
    WaitForSingleObject(thread->thread, INFINITE);
    return thread->result;
}

void univthread_cancel(struct UnivThread *thread)
{
    // FIXME: Handle errors correctly.
    BOOL result = TerminateThread(thread->thread, 0);
}

void univthread_destroy(struct UnivThread *thread)
{
    univthread_cancel(thread);
    univthread_join(thread);
    free(thread);
}

void univthread_suspend(struct UnivThread *thread)
{
    DWORD result = SuspendThread(thread->thread);

    if (result)
    {
        // FIXME: Handle errors.
    }
}

void univthread_resume(struct UnivThread *thread)
{
    DWORD result = ResumeThread(thread->thread);

    if (result)
    {
        // FIXME: Handle errors.
    }
}

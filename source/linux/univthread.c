/**
 *  @brief Source definition for UnivThread on the Linux platform.
 */

#include <stdlib.h>
#include <signal.h>

#include <linux/univthread.h>

void signal_resume_handler(int signal)
{

}

static void signal_suspend_handler(int signal)
{
    // Once we hit the suspend handle, wait for SIGUSR2 to say we're safe to resume.
    sigset_t signalSet;
    sigemptyset(&signalSet);

    // FIXME: We're waiting for a signal in a signal handler - is this safe to do?
    if(sigaddset(&signalSet, SIGUSR2) == -1) {
        // FIXME: Handle error?
        return;
    }

    int capturedSignal = 0;
    sigwait(&signalSet, &capturedSignal);
}

static void* internalStartRoutine(void *parameter)
{
    struct UnivThread *thread = (struct UnivThread*)parameter;

    // Before we execute, setup our suspend signal
    signal(SIGUSR1, signal_suspend_handler);
    signal(SIGUSR2, signal_resume_handler);
    void *result = thread->startRoutine(thread->parameter);

    return result;
}

struct UnivThread* univthread_create(ThreadStartRoutine startRoutine, void *parameter)
{
    int callResult = 0;

    struct UnivThread *result = calloc(1, sizeof(struct UnivThread));
    result->parameter = parameter;
    result->startRoutine = startRoutine;

    // Attempt to init the attributes
    if ((callResult = pthread_attr_init(&result->attributes)) != 0)
    {
        free(result);
        return NULL;
    }

    // Init the thread itself
    if ((callResult = pthread_create(&result->thread, &result->attributes, &internalStartRoutine, (void*)result)) != 0)
    {
        free(result);
        return NULL;
    }

    return result;
}

void* univthread_join(struct UnivThread *thread)
{
    int callResult = 0;
    void* threadResult = NULL;

    if ((callResult = pthread_join(thread->thread, &threadResult)) != 0)
    {
        // FIXME: Handle this error properly.
        return NULL;
    }

    return threadResult;
}

void univthread_cancel(struct UnivThread *thread)
{
    int callResult = 0;

    if ((callResult = pthread_cancel(thread->thread)) != 0)
    {
        // FIXME: Handle error properly.
        return;
    }
}

void univthread_destroy(struct UnivThread *thread)
{
    univthread_cancel(thread);
    univthread_join(thread);

    int callResult;
    if ((callResult = pthread_attr_destroy(&thread->attributes)) != 0)
    {
        // FIXME: Handle error properly.
    }

    free(thread);
}

void univthread_suspend(struct UnivThread *thread)
{
    int callResult = 0;
    if ((callResult = pthread_kill(thread->thread, SIGUSR1)) != 0)
    {
        // FIXME: Handle errors.
    }
}

void univthread_resume(struct UnivThread *thread)
{
    int callResult = 0;
    if ((callResult = pthread_kill(thread->thread, SIGUSR2)) != 0)
    {
        // FIXME: Handle errors.
    }
}

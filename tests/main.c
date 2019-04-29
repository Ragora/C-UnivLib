#include <stdlib.h>

#include <univmutex.h>
#include <univthread.h>

void *suspendResumeThread(void *parameter)
{
    while (1)
    {
        printf("Outputting ...\n");
        sleep(1);
    }

    return NULL;
}

int main()
{
    printf("Initializing thread ...\n");
    struct UnivThread *result = univthread_create(suspendResumeThread, NULL);
    if (!result)
    {
        printf("Bad thread!\n");
        return -1;
    }

    printf("Waiting 4 seconds ...\n");
    sleep(4);

    printf("Sending suspend signal ...\n");
    univthread_suspend(result);

    printf("Waiting 4 seconds ...\n");
    sleep(4);

    printf("Resuming ...\n");
    univthread_resume(result);
    printf("Waiting 4 seconds ...\n");
    sleep(4);

    printf("Destroying ...\n");
    univthread_destroy(result);

    struct UnivMutex *mutex = univmutex_create();
    univmutex_lock(mutex);
    univmutex_destroy(mutex);

    return 0;
}

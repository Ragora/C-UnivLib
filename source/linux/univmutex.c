/**
 *  @brief Source definition for UnivMutex on the Linux platform.
 */

#include <stdlib.h>

#include <linux/univmutex.h>

struct UnivMutex* univmutex_create(void)
{
    struct UnivMutex *result = (struct UnivMutex*)calloc(1, sizeof(struct UnivMutex));

    int callResult = 0;
    //pthread_mutexattr_t mutexAttributes;

    if ((callResult = pthread_mutex_init(&result->internal, NULL)) != 0)
    {
        free(result);
        return NULL;
    }

    return result;
}

void univmutex_lock(struct UnivMutex *mutex)
{
    pthread_mutex_lock(&mutex->internal);
}

void univmutex_unlock(struct UnivMutex *mutex)
{
    pthread_mutex_unlock(&mutex->internal);
}

void univmutex_destroy(struct UnivMutex *mutex)
{
    univmutex_unlock(mutex);

    pthread_mutex_destroy(&mutex->internal);
    free(mutex);
}

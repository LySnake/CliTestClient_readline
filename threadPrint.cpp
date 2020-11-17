#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "ReadlineWrap.h"



static unsigned int iSleepTime = 3;
static pthread_t tid;
static int ThreadRunFlag = 1;


static void do_something()
{
    ThreadRunFlag = 1;
    while (ThreadRunFlag)
    {
        sleep(iSleepTime);
        printf("\npthread print log:  %s.\n", rl_line_buffer);

        rl_on_new_line();
        rl_redisplay();
    }
    
}

void StartThread()
{
    int ret = pthread_create(&tid, NULL, do_something, NULL);
    if( ret != 0) {
        printf("pthread_create fail. ret = %d\n", ret);
    }
}

void StopThread()
{
    ThreadRunFlag = 0;
    pthread_join(tid, NULL);
}
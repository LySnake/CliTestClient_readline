#include <stdio.h>
#include <chrono>

#include "ReadlineWrap.h"
#include "PrintThread.h"

const unsigned int iSleepTime = 3;


PrintThread::PrintThread():ThreadRunFlag(true),p_PrintThread(nullptr)
{
    startThread();
}

PrintThread::~PrintThread()
{
    stopThread();
}

void PrintThread::startThread()
{
    p_PrintThread = new std::thread(&PrintThread::DoPrint, this);
}

void PrintThread::DoPrint()
{
    while (ThreadRunFlag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3 * 1000));
        printf("\npthread print log:  %s.\n", rl_line_buffer);

        rl_on_new_line();
        rl_redisplay();
    }
    
}

void PrintThread::stopThread()
{
    ThreadRunFlag = false;

    if(p_PrintThread)
    {
        p_PrintThread->join();
        p_PrintThread = nullptr;
    }
}

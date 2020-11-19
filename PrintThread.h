#ifndef __PRINT_THREAD_H__
#define __PRINT_THREAD_H__

#include <memory>
#include <thread>


class PrintThread
{
public:
    PrintThread();
    ~PrintThread();
private:
    void startThread();
    void stopThread();
    void DoPrint();

private:
    bool  ThreadRunFlag;
    std::thread *p_PrintThread;
};



#endif //__PRINT_THREAD_H__
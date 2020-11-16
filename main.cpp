#include "ReadlineWrap.h"
#include "Commands.h"
// #include "threadPrint.h"

int main(int argc, char *argv[])
{
    initializeCommands();

    // StartThread();
    ReadlineWrap::getInstance()->runReadline();
    // StopThread();

    exit(0);
}
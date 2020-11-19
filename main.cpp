#include "ReadlineWrap.h"
#include "CommandList.h"
#include "PrintThread.h"

int main(int argc, char *argv[])
{
    initializeCommands();

    PrintThread AsynPrint;  //异步打印，验证终端显示
    ReadlineWrap::getInstance()->runReadline();

    exit(0);
}
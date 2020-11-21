#include "ReadlineWrap.h"
#include "CommandList.h"
#include "PrintThread.h"


#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h" // for loading levels from the environment variable

int main(int argc, char *argv[])
{
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    initializeCommands();

    PrintThread AsynPrint;  //异步打印，验证终端显示
    ReadlineWrap::getInstance()->runReadline();

    exit(0);
}
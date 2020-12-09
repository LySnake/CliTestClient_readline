#include "ReadlineWrap.h"
#include "CommandList.h"
#include "PrintThread.h"

#include "spdlog/cfg/env.h"
#include "project.h"

int main(int argc, char *argv[])
{
    spdlog::info("Spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    initializeCommands();

    PrintThread AsynPrint;  //异步打印，验证终端显示
    ReadlineWrap::getInstance()->runReadline();

    exit(0);
}
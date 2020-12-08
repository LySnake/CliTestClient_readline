#include "Backtrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
 
constexpr size_t MAX_TRACE_DEEP = 20;
constexpr size_t BUFF_SIZE = 1024;
const std::string FILENAME = "a.out";
 
void print_trace (void)
{
    void *array[MAX_TRACE_DEEP];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, MAX_TRACE_DEEP);
	strings = backtrace_symbols(array, size);
    if (NULL == strings)
    {
        perror("backtrace_synbols");
        return;
    }

    for (i = 0; i < size; i++) {
        char buf[BUFF_SIZE];
        std::stringstream cmd;
        cmd << "addr2line " << array[i] << " -e " << FILENAME << " -fisp";
        FILE *p_Pip = popen(cmd.str().c_str(), "r");
        if(!p_Pip) {
            perror("popen fail.");
            continue;
        }

        char *str = fgets(buf, sizeof(buf), p_Pip);
        if(str != buf) {
            perror("fgets fail.");
            pclose(p_Pip);
            continue;
        }

        printf("%s", str);
        pclose(p_Pip);
    }
}

int test2() {
    print_trace();
    return 0;
}

int test1() {
    return test2();
}
int test() {
    return test1();
}

int main()
{
    return test();
}

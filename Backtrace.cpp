#include "Backtrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
 
constexpr size_t MAX_TRACE_DEEP = 20;
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
    for(i = 0; i < size; i++) {
        printf("--%s \n", strings[i]);
    }


    for (i = 0; i < size; i++) {
        std::stringstream cmd;
        cmd << "addr2line " << array[i] << " -e " << FILENAME << " -fisp";
        system(cmd.str().c_str());
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

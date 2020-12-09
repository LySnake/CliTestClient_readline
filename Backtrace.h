#ifndef __BACKTRACE_H__
#define __BACKTRACE_H__


#include <execinfo.h>
#include <stdio.h>
namespace tool {
    void Backtrace(size_t depth = 1);
} //namespace tool

#endif // __BACKTRACE_H__
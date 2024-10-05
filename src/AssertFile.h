#ifndef ASSERT_CUSTOM
#define ASSERT_CUSTOM

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <ColorPrintFile.h>

#define ASSERT(TestFile, ErrorStr) SpecAssert(TestFile, ErrorStr, __FILE__, __PRETTY_FUNCTION__, __LINE__)

int SpecAssert    (int x, const char *ErrorStr, const char *file, const char *func, int line);
int SpecAssert(int x, const char *ErrorStr, const char *file, const char *func, int line) {
    
    assert(ErrorStr);
    assert(file);
    assert(func);
    
    if (!x) {
        RED_PRINT_ARG("Error:\n"
                      "File:      %s\n"
                      "Function:  %s\n"
                      "Line:      %d\n"
                      "%s\n", file, func, line, ErrorStr);
        abort();
    }

    return 0;
}

#endif // ASSERT_CUSTOM
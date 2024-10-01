#ifndef ColorPrint
#define ColorPrint

#include <stdarg.h>

#define GREEN_SYMBOLS       "\033[1;32m"
#define RED_SYMBOLS         "\033[1;31m"
#define CYAN_SYMBOLS        "\033[1;36m"
#define YELLOW_SYMBOLS      "\033[1;33m"
#define DEFAULT_COLOR       "\033[0m"
#define LIGHTWHITE_SYMBOLS  "\033[1;37m"

#define WHITE_PRINT(exp)           printf(LIGHTWHITE_SYMBOLS exp DEFAULT_COLOR)
#define WHITE_PRINT_ARG(exp, ...)  printf(LIGHTWHITE_SYMBOLS exp DEFAULT_COLOR, __VA_ARGS__)

#define RED_PRINT(exp)             printf(RED_SYMBOLS exp DEFAULT_COLOR)
#define RED_PRINT_ARG(exp, ...)    printf(RED_SYMBOLS exp DEFAULT_COLOR, __VA_ARGS__)

#define YELLOW_PRINT(exp)          printf(YELLOW_SYMBOLS exp DEFAULT_COLOR)
#define YELLOW_PRINT_ARG(exp, ...) printf(YELLOW_SYMBOLS exp DEFAULT_COLOR, __VA_ARGS__)

#define CYAN_PRINT(exp)            printf(CYAN_SYMBOLS exp DEFAULT_COLOR) 
#define CYAN_PRINT_ARG(exp, ...)   printf(CYAN_SYMBOLS exp DEFAULT_COLOR, __VA_ARGS__)

#define GREEN_PRINT(exp)           printf(GREEN_SYMBOLS exp DEFAULT_COLOR)
#define GREEN_PRINT_ARG(exp, ...)  printf(GREEN_SYMBOLS exp DEFAULT_COLOR, __VA_ARGS__)


#endif // ColorPrint
#include <stdio.h>
#include "logger.h"

#ifdef _WIN32
    #include <windows.h>
    #define RED     FOREGROUND_RED
    #define GREEN   FOREGROUND_GREEN
    #define WHITE   FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#else
    #define RED     "\x1b[31m"
    #define GREEN   "\x1b[32m"
    #define WHITE   "\x1b[0m"
#endif

void log_error(const char *message) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, RED);
        printf("Error: %s\n", message);
        SetConsoleTextAttribute(hConsole, WHITE);
    #else
        printf("%sError: %s%s\n", RED, message, WHITE);
    #endif
}

void log_success(const char *message) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        printf("%s\n", message);
        SetConsoleTextAttribute(hConsole, WHITE);
    #else
        printf("%s%s%s\n", GREEN, message, WHITE);
    #endif
}
#include <cstdio>

#define SHOW_DEBUGLOG 1
#define SHOW_LOGINFO 1
#define SHOW_LOGWARNING 0
#define SHOW_LOGERROR 1
#define SHOW_LOGDEBUG 1
#define SHOW_LOGNOCAT 0

// Defines log categories
enum LogCategory {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_DEBUG
};

// Logging macro
#if SHOW_DEBUGLOG
    #define DEBUG_LOG(LogCategory, Msg, ...) \
        do { \
            const char* categoryStr; \
            bool shouldLog = false; \
            switch (LogCategory) { \
                case LOG_INFO:    categoryStr = "INFO"; shouldLog = SHOW_LOGINFO; break; \
                case LOG_WARNING: categoryStr = "WARNING"; shouldLog = SHOW_LOGWARNING; break; \
                case LOG_ERROR:   categoryStr = "ERROR"; shouldLog = SHOW_LOGERROR; break; \
                case LOG_DEBUG:   categoryStr = "DEBUG"; shouldLog = SHOW_LOGDEBUG; break; \
                default:          categoryStr = "UNKNOWN"; shouldLog = SHOW_LOGNOCAT; break; \
            } \
            if (shouldLog) { \
                printf("[%s] ", categoryStr); \
                printf(Msg, ##__VA_ARGS__); \
                printf("\n"); \
            } \
        } while (0)
#else
    #define DEBUG_LOG(LogCategory, Msg, ...)
#endif
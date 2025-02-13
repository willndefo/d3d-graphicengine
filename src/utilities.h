#pragma once

#include <cstdio>
#include <sstream>
#include <string>
#include <fstream>

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


// Shader compiler config
#define PS_ENTRYPOINT "main"
#define PS_VERSION "ps_5_0"
#define VS_ENTRYPOINT "main"
#define VS_VERSION "vs_5_0"


namespace GUtilities
{
    static std::string GetProjectDirectory()
    {
        std::string fullPath(__FILE__);
        size_t found = fullPath.find_last_of("/\\");

        if (found != std::string::npos)
        {
            std::string projectDir = fullPath.substr(0, found + 1);
            return projectDir;
        }

        return "";
    }

    static std::string ReadHLSLFile(std::string&& FileName, std::string&& SubDirectory = "")
    {
        const std::string shaderPath = GetProjectDirectory() + "Shaders\\" + SubDirectory + FileName;
        std::ifstream file(shaderPath);

        if (!file.is_open())
        {
            DEBUG_LOG(LOG_ERROR, "Failed to open the shader : %s", shaderPath.c_str());
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }
}



#include <exception>
#include <stdio.h>
#include <cstring>
#include "logging.h"
#include <string>

using std::exception;

void Logger::LogEvent(const char *event)
{
    if(Logger::logger == NULL)
    {
        Logger::logger = fopen((char*) "logger", "w");
    }
    fwrite(event, strlen(event), 1, logger);
    fwrite("\n", 1, 1, logger);
}

void Logger::Finalize()
{
    fclose(logger);
}

FILE* Logger::logger;

DataFlowException::DataFlowException(const char *type, const char *error)
{
    // too hacky?
    strcpy(msg, "(");
    strcat(msg, type);
    strcat(msg, "): ");
    strcat(msg, error);
    Logger::LogEvent(msg);
}


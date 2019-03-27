#ifndef MLOGGER_H
#define MLOGGER_H

#include <map>
#include <mutex>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>

#include "outputs.h"

using namespace std;

typedef enum LOG_LEVEL
{
    LEVEL_DEFAULT,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_VERBOSE,
    ENUM_END
}eLogLevel;

class OutputLogs;

class MLoggerBase
{
    map<eLogLevel , vector<OutputLogs *> > registryMap;
    string data;

public:
    //Register Log level with Type of Log output source
    void registerLog( eLogLevel eLevel, OutputLogs * pOut);

    //Inform Log output source about the Data received for logging
    void signal(eLogLevel eLevel, string strData);
};

class MLogger : public MLoggerBase
{
    MLogger();
    static MLogger *m_pLogger;
    map<eLogLevel, bool> messageStatusMap;
    static mutex m_amoticSingelton;

public:
    //Log level, and user input has to be converted into String.
    void writeLog(eLogLevel eLevel, string strData, string strArg);

    //Enable Logging by providing the Log level.
    void enableLog(eLogLevel eLevel);

    //Disable Logging by providing the Log level.
    void disableLog(eLogLevel eLevel);

    static MLogger* getLoggerInstance();
};

#endif //MLOGGER

#ifndef OUTPUTS_H
#define OUTPUTS_H

#include <fstream>
#include <mutex>

#include "mlogger.h"

using namespace std;

//Forward Declaration of MLoggerBase
class MLoggerBase;

class OutputLogs
{
public:
    virtual void writeToOutput(MLoggerBase *pLogger, string strData) = 0;
    virtual ~OutputLogs(){}
};

//Output Log into Console
class Console : public OutputLogs
{
    std::mutex m_synchConsoleOutput;
public:
    Console();
    void writeToOutput(MLoggerBase *pLogger, string strData);

    ~Console();
};

//Output Log into File
class File : public OutputLogs
{
private:
    string m_strLogFileName;
    ofstream m_outFile;
    std::mutex m_synchFileWrite;

public:
    File(string strName);
    void writeToOutput(MLoggerBase *pLogger, string strData);

    ~File();
};

#endif // OUTPUTS_H

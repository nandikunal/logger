#include "mlogger.h"

MLogger* MLogger::m_pLogger = nullptr;
mutex MLogger::m_amoticSingelton;

/*=====================================================================
//  MLoggerBase Class
=======================================================================*/
void MLoggerBase::registerLog(eLogLevel eLevel, OutputLogs *pOut)
{
    if(LEVEL_VERBOSE == eLevel) //Enable All the Logs
    {
        registryMap.clear();
        for(int i = LEVEL_DEFAULT; i < ENUM_END; i++)
        {
            registryMap[static_cast<eLogLevel>(i)].push_back(pOut);
        }
    }
    else
    {
        registryMap[eLevel].push_back(pOut);
    }
}

void MLoggerBase::signal(eLogLevel eLevel, string strData)
{
    map<eLogLevel , vector<OutputLogs *> >::iterator it = registryMap.find(eLevel);
    if(it != registryMap.end())
    {
        for(vector<OutputLogs *>::iterator itV = it->second.begin(); itV != it->second.end(); itV++)
        {
            (*itV)->writeToOutput(this, strData);
        }
    }
}

/*=====================================================================
//  MLogger Class
=======================================================================*/
MLogger* MLogger::getLoggerInstance()
{
    //Adding Double-Checked Locking Pattern - Making Instance creation thread-safe.
    if(!m_pLogger)
    {
        lock_guard<mutex> lock(m_amoticSingelton);

        if(!m_pLogger)
        {
            m_pLogger = new MLogger();
        }
    }
    return m_pLogger;
}

MLogger::MLogger()
{
    messageStatusMap[LEVEL_DEFAULT] = true;
    messageStatusMap[LEVEL_ERROR] = true;
    messageStatusMap[LEVEL_INFO] = true;
    messageStatusMap[LEVEL_WARNING] = true;
}

void MLogger::writeLog(eLogLevel type, string strData, string strArg)
{
    strData.append(static_cast<string>(strArg));

    if(messageStatusMap[type])
    {
        signal(type, strData);
    }
}

void MLogger::enableLog(eLogLevel type)
{
    messageStatusMap[type] = true;
}

void MLogger::disableLog(eLogLevel type)
{
    messageStatusMap[type] = false;
}

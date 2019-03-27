#include "outputs.h"
#include <string>

/*=====================================================================
//  Handling of Log output to File
=======================================================================*/
File::File(string strName):m_strLogFileName(strName)
{
    m_outFile.open(m_strLogFileName.c_str(), ios::app);

    if(m_outFile.fail())
    {
        cout << "Fail to Open the File!";
    }
}

File::~File()
{
    if(m_outFile.is_open())
    {
        m_outFile.close();
    }
}

void File::writeToOutput(MLoggerBase *pLogger, string strData)
{
    if(!m_outFile.is_open())
    {
        m_outFile.open(m_strLogFileName.c_str(), ios::app);
        if(m_outFile.fail())
        {
            cout << "Fail to Open the File!";
        }
    }

    std::lock_guard<std::mutex> lock(m_synchFileWrite);
    m_outFile << strData << endl;
}

/*=====================================================================
//  Handling of Log output to Console
=======================================================================*/
Console::Console()
{

}

Console::~Console()
{

}

void Console::writeToOutput(MLoggerBase *pLogger, string strData)
{
    std::lock_guard<std::mutex> lock(m_synchConsoleOutput);
    cout << strData << endl;
}

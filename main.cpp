#include "mlogger.h"
#include <thread>

using namespace std;

MLogger *pLogger = MLogger::getLoggerInstance();    //Get Logger Instance

Console *ptrConsole = new Console();        //Get Instance of Console Output, which needs to be registered for Log LEVEL.
File *ptrFile = new File("hello.log");      //Get Instance of File Output (With file name), which needs to be registered for Log LEVEL.

void printLogThread1()
{
    pLogger->writeLog(LEVEL_INFO, "INFO", ": THREAD1");
    pLogger->writeLog(LEVEL_WARNING, "WARNING", ": THREAD1"); //This log will not be seen in File, WARNING LEVEL is not registered with File output.
}

void printLogThread2()
{
    pLogger->writeLog(LEVEL_INFO, "INFO", ": THREAD2");
    pLogger->writeLog(LEVEL_WARNING, "WARNING", ": THREAD2"); //This log will not be seen in File, WARNING LEVEL is not registered with File output.
}

int main()
{
    std::thread t1(printLogThread1);
    std::thread t2(printLogThread2);

    pLogger->registerLog(LEVEL_VERBOSE, ptrConsole);    //Register all log level for Console output
    pLogger->registerLog(LEVEL_ERROR, ptrFile);         //Register ERROR log for File output
    pLogger->registerLog(LEVEL_INFO, ptrFile);          //Register INFO log for File output

    pLogger->writeLog(LEVEL_ERROR, "ERROR", ": I am Error Text");
    pLogger->writeLog(LEVEL_DEFAULT, "DEFAULT", ": I am Default Text");
    pLogger->writeLog(LEVEL_INFO, "INFO", ": I am Info Text");
    pLogger->writeLog(LEVEL_WARNING, "INFO", ": I am Warning Text");    //This log will not be seen in File, WARNING LEVEL is not registered with File output.

    pLogger->disableLog(LEVEL_INFO);
    pLogger->writeLog(LEVEL_INFO, "INFO", ": Logs after Disabling Log level");  //This log won't be seen on console

    pLogger->enableLog(LEVEL_INFO);
    pLogger->writeLog(LEVEL_INFO, "INFO", ": Logs after Enabling Log level");  //This log will be seen on console

    t1.join();
    t2.join();

    delete ptrConsole;
    delete ptrFile;
    delete pLogger;

    return 0;
}

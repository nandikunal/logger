#### Logger Framework

# Application Usage and Area of Improvement
    
    • It allows to output logs on Console (stdout) and File (Input given by user)
    • Logger application allows adding Different level of Logs, which will facilitate application have distinguished Log level like
        1. LEVEL_DEFAULT
        2. LEVEL_INFO
        3. LEVEL_WARNING
        4. LEVEL_ERROR
        5. LEVEL_VERBOSE
        
    • “mlogger.h” needs to be included in application to get the writeLog() api access, which allows to add log with three parameters.
        1. Log LEVEL
        2. String
        3. String
        
    • User defined data type needs to be passed as String argument.
    • After registering Output with Level, it can be disabled when not in used and can be enabled using disableLog() and enableLog() api respectively.
    • main.cpp is a unit test application which will help to understand the use of Logger Class.

# Area of Improvement - Currently Working on
    1. User defined data type input support, not limiting to pass only string as parameter.
    2. Output logs to Network on Socket.
    3. Adding Timestamp in every log output which can be useful for KPI Measurement.
    4. Adding Unit test

# Design Description 

    1. Logger Framework is developed using Observer pattern, and Intension of having Observer patter in Logger application to fulfil MLoggerBase class notifying Observers (OutputLogs – File & Console), whenever there is, new log needs to be put on Console and/or File.
    2. MLogger class is defined as Singleton, to avoid having multiple instance of MLogger class, which will be same throughout the lifecycle.
    3. Observer class File and Console are derived from OutputLogs which will in turn helps to logs the output according to Registered output Class for particular log level, which will decided on runtime in MLoggerBase signal() function.

# Class Diagram of Logger Framework can be found in root directory.

# How to & Reference

    1. Code is developed in Linux [Ubuntu 18.04.1 LTS]
    2. Compiler used GNU GCC enabling “–std=C++11” [MinGW]
    3. StarUML is used for Class diagram
    
#### How to Compile

cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild -H.
cd build/
make -j8

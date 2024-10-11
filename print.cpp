#include "print.h"
#include <iostream>
#include <ostream>
#include <QTime>

LogPrint::Log* LogPrint::Log::m_instance = nullptr;

void LogPrint::Log::printINFO(const QString text)
{
    if(getDebugLevel() >= DebugLevel::MESSAGE_INFO)
    {
        writeMessage(("INFO  |" + QTime::currentTime().toString() + "| " + text).toStdString(), Log::DebugLevel::MESSAGE_INFO);
        // appendToFile(text);
    }
}

void LogPrint::Log::printWARN(const QString text)
{
    if(getDebugLevel() >= Log::DebugLevel::MESSAGE_WARNING)
    {
        writeMessage(("WARN  |" + QTime::currentTime().toString() + "| " + text).toStdString(), Log::DebugLevel::MESSAGE_WARNING);
        // appendToFile(text);
    }
}

void LogPrint::Log::printERR(const QString text)
{
    if(getDebugLevel() >= Log::DebugLevel::MESSAGE_ERROR)
    {
        writeMessage(("ERROR |" + QTime::currentTime().toString() + "| " + text).toStdString(), Log::DebugLevel::MESSAGE_ERROR);
        // appendToFile(text);
    }
}

void LogPrint::Log::print(const QString text)
{
    writeMessage(text.toStdString(), Log::DebugLevel::MESSAGE_DEFAULT);
}

LogPrint::Log *LogPrint::Log::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Log{};
    }
    return m_instance;
}

void LogPrint::Log::setDebugLevel(DebugLevel level)
{
    m_DebugLevel = level;
}

LogPrint::Log::DebugLevel LogPrint::Log::getDebugLevel()
{
    return m_DebugLevel;
}

void LogPrint::Log::writeMessage(const std::string &message, DebugLevel type)
{

    switch (type)
    {
        case MESSAGE_ERROR:
        {
            std::cout << "\e[1;31m" << message << "\e[0m" << std::endl;
            break;
        }
        case MESSAGE_WARNING:
        {
            std::cout << "\e[1;33m" << message << "\e[0m" << std::endl;
            break;
        }
        case MESSAGE_INFO:
        {
            std::cout << "\e[1;32m" << message << "\e[0m" << std::endl;
            break;
        }
        default:
        {
            std::cout << message << std::endl;
            break;
        }
    }
}


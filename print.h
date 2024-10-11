#ifndef PRINT_H
#define PRINT_H

#include <QString>
#include <memory>
#include <QObject>

#define  LOG_ERR(TEXT)  LogPrint::Log::getInstance()->printERR(TEXT)
#define  LOG_WARN(TEXT) LogPrint::Log::getInstance()->printWARN(TEXT)
#define  LOG_INFO(TEXT) LogPrint::Log::getInstance()->printINFO(TEXT)
#define  print_(TEXT)   LogPrint::Log::getInstance()->print(TEXT)

namespace LogPrint
{
// #define  LOG_INFO(TEXT) getInstance()->printINFO(TEXT)


    class Log: public QObject
    {
        Q_DISABLE_COPY(Log)
        Q_OBJECT;

    public:
        static Log *instance();

        enum DebugLevel
        {
            MESSAGE_DEFAULT,
            MESSAGE_ERROR,
            MESSAGE_WARNING,
            MESSAGE_INFO
        };

        void setDebugLevel(DebugLevel level);
        DebugLevel getDebugLevel();

        void printINFO(const QString text);
        void printWARN(const QString text);
        void printERR(const QString text);
        void print(const QString text);
        static Log* getInstance();

        void setInstance(Log *newInstance);

    private:
        explicit Log(QObject *parent = nullptr){};
        virtual ~Log() {}
        static Log* m_instance;

        void writeMessage(const std::string &message, DebugLevel type);
        void appendToFile(const std::string& message);

        DebugLevel m_DebugLevel;

    protected:
    };

};

#endif // PRINT_H

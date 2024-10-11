#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <back.h>
#include <QThread>
#include <print.h>

using namespace LogPrint;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/untitled/main.qml"));

    // log init //////////////////////////////////////////////////////////////////////////////////////
    LogPrint::Log::getInstance()->setDebugLevel(LogPrint::Log::MESSAGE_INFO);

    // LOG_ERR("error");
    // LOG_WARN("warning");
    // LOG_INFO("info");
    // print_("Hello word");
    // log //////////////////////////////////////////////////////////////////////////////////////

    //============================
    // init back
    Back back;
    QThread backThread;
    backThread.setObjectName("backThread");
    back.moveToThread(&backThread);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &back, &Back::start);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            LOG_INFO(" start objectCreated");
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

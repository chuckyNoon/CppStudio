#ifndef THREADHELPER_H
#define THREADHELPER_H

#include <functional>
#include <QtConcurrent/QtConcurrent>

class ThreadHelper
{
public:
    ThreadHelper();

    static void dispatchDelayed(int delaySeconds, std::function<void()> callback)
    {
        auto result = QtConcurrent::run(
            [](int delaySeconds, std::function<void()> callback){
                QThread::sleep(delaySeconds);
                callback();
            },
            delaySeconds,
            callback
            );
    }

    static void dispatchToMainThread(std::function<void()> callback)
    {
        //QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        // any thread
        QTimer* timer = new QTimer();
        timer->moveToThread(qApp->thread());
        timer->setSingleShot(true);
        QObject::connect(timer, &QTimer::timeout, [=]() {
            // main thread
            callback();
            timer->deleteLater();
        });
        QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, 0));
    }

};

#endif // THREADHELPER_H

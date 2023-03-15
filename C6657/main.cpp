#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <string>
#include <cstdio>
#include <cstring>

#include "wmain.h"
#include <QApplication>
#include "ioworker.h"

void customMessageHandler(QtMsgType type,
    const QMessageLogContext& context,
    const QString& msg)
{
    //Q_UNUSED(context)
    static QMutex mutex;
    QDateTime _datetime = QDateTime::currentDateTime();
    QString szDate = _datetime.toString("[mm:ss.zzz][");//"yyyy-MM-dd hh:mm:ss ddd"
    QString txt(szDate);
    txt.append(QString::number(type));
    txt.append(QString("][%1:").arg(context.file));
    txt.append(QString("%1]").arg(context.line));
    txt.append(msg);

    mutex.lock();
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << txt << "\r\n";
    file.close();
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customMessageHandler);
    qDebug() << "------------------------main()-------------------------------";
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        qDebug() << "WSAStartup error.";

        return -1;
    }

    IoWorker worker;
    Widget w(&worker);

    w.show();
    
    int ret=a.exec();
    worker.wait();
    return ret;
}

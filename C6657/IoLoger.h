#pragma once
#include <cstdint>
#include <qlist.h>

class IIoLoger {
public:
    virtual void chardump(bool in, char* data, size_t size) = 0;
    virtual void uint32dump(bool in, uint32_t* data, size_t ) = 0;
    virtual void register_filter(QList<uint16_t>& f) = 0;
};

#include <QTextStream>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QDebug>
class PlainTextEditLoger : public IIoLoger {
private:
    QPlainTextEdit* edit;
    QList<uint16_t> filters;
public:
    PlainTextEditLoger(QPlainTextEdit* e)
        :edit(e)
    {

    }

    void register_filter(QList<uint16_t>& f)
    {
        filters = f;
    }

    void log_qbytearray(QByteArray& ba,bool in)
    {
        QString line;
        QTextStream loger(&line);
        QDateTime _datetime = QDateTime::currentDateTime();
        QString szDate = _datetime.toString("[mm:ss.zzz]");
        loger << szDate << (in ? "I:" : "O:");
        loger.setIntegerBase(16);
        loger << ba.toHex(' ');
        loger << "\n";
        edit->textCursor().insertText(line);
        qDebug() << line;
    }

    void chardump(bool in, char* data, size_t size)
    {
        QByteArray ba(data, size);
        log_qbytearray(ba,in);
    }

    void uint32dump(bool in, uint32_t* data, size_t size)
    {
        QByteArray all;
        
        for (uint16_t i : filters) {
            QByteArray one( (char*)(data + i), 4);
            all.push_back(one);
        }
        log_qbytearray(all,in);
    }
};
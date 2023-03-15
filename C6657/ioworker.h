#ifndef IOWORKER_H
#define IOWORKER_H

#include <QThread>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "c6657serialport.h"
#include "c6657udp.h"

class C6657Udp;
class C6657SerialPort;
class boost::asio::io_context;
class IIoLoger;
class IIoSender;
class IoWorker : public QThread
{
    Q_OBJECT
public:
    IoWorker();
    void registerLoger(IIoLoger* ul, IIoLoger* sl);
    void run() override ;
public slots:
    void stop();
    IIoSender* udp_sender() { return udp; }
    IIoSender* serial_sender() { return serialport; }
private:
    C6657Udp* udp;
    IIoLoger* udp_loger;
    C6657SerialPort* serialport;
    IIoLoger* serial_loger;
    boost::asio::io_context* iocontext;
};

#endif // IOWORKER_H

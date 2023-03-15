#include "ioworker.h"
#include "c6657udp.h"
#include "c6657serialport.h"
#include "udpincomingprocessor.h"
#include "serialincomingprocessor.h"

IoWorker::IoWorker()
    :iocontext(nullptr)
{

}

void IoWorker::registerLoger(IIoLoger* ul, IIoLoger* sl)
{
    this->udp_loger = ul;
    this->serial_loger = sl;
}

void IoWorker::run()
{

    boost::asio::io_context io_context;
    iocontext=&io_context;

    ////// c6657 udp

    udp = new C6657Udp(io_context,new UdpIncomingProcessor(udp_loger) );

    ////// c6657 serial port
    serialport = new C6657SerialPort(io_context, new SerialIncomingProcessor(serial_loger));

    io_context.run();
}

void IoWorker::stop()
{
    if(iocontext){
        iocontext->stop();
        while( !iocontext->stopped() ){
            msleep(1);
        }
    }
}


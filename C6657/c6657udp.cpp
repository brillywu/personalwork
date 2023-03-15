#include "c6657udp.h"
#include <QDebug>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "udpincomingprocessor.h"

#define LOCALIP
#ifdef LOCALIP
const char *hisip="127.0.0.1";
const int hisport=6657;
const char *myip="127.0.0.1";
const int myport=6658;
#else
const char *hisip="192.168.1.47";
const int hisport=6657;
const char *myip="192.168.1.57";
const int myport=6657;

#endif

using namespace  boost::asio;

C6657Udp::C6657Udp(boost::asio::io_context &io_context,
    IIncomingProcessor* p,
    QObject *parent)
    : QObject(parent)
    , IIoReceiver(io_context)
    , socket(io_context)
    , there(boost::asio::ip::make_address_v4( hisip ), hisport)
    , processor(p)
{
    boost::system::error_code ec;
    boost::asio::ip::udp::endpoint me(boost::asio::ip::make_address_v4( myip),myport);

    do {
        socket.open(ip::udp::v4(),ec);
        if( ec ){
            qDebug() << "socket open error:" << ec.message().c_str();
            break;
        }

        socket.bind( me ,ec);
        if( ec ){
            qDebug() << "socket bind return:" << ec.message().c_str() ;
            break;
        }
        issue_async_read();
    }while(0);
}

void C6657Udp::issue_async_read()
{
    recv_buffer = frames.malloc();
    socket.async_receive_from(
            boost::asio::buffer(*recv_buffer), there,
            boost::bind(&C6657Udp::data_recieved, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}


void C6657Udp::data_recieved(const boost::system::error_code &ec, size_t bytes_transferred)
{
    if(  !ec ) {
        processor->new_frame_arrived( recv_buffer, bytes_transferred );
        issue_async_read();
    } else {
        qDebug() <<"data_recieved error:"<< ec.message().c_str();
    }
    frames.free(recv_buffer);

}


long C6657Udp::send(const char *data, size_t bytes)
{
    return socket.send_to( boost::asio::buffer(data,bytes) ,there);
}

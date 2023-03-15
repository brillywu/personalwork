#include "c6657serialport.h"
#include <boost/bind.hpp>
#include "qdebug.h"
using namespace boost::asio;

C6657SerialPort::C6657SerialPort(boost::asio::io_context &io_context, 
    IIncomingProcessor* p,
    QObject *parent)
    : QObject(parent)
    , IIoReceiver(io_context)
    , serial_c6657(io_context.get_executor())
    , processor( p )
{
    boost::system::error_code ec;
    serial_c6657.open("COM3",ec);
    if( !ec && serial_c6657.is_open() ){
        serial_c6657.set_option(serial_port::baud_rate( 19200 ) );  //比特率
        serial_c6657.set_option(serial_port::flow_control( serial_port::flow_control::none ) ); //流量控制
        serial_c6657.set_option(serial_port::parity( serial_port::parity::odd ) );            //奇偶校验
        serial_c6657.set_option(serial_port::stop_bits(  serial_port::stop_bits::one ) );        //停止位
        serial_c6657.set_option(serial_port::character_size( 8 ) );                       //数据位

        issue_async_read();
    } else {
        qDebug() << "open serial error:"<<ec.message().c_str();
    }
}

C6657SerialPort::~C6657SerialPort()
{

}

void C6657SerialPort::issue_async_read()
{

    recv_buffer = frames.malloc();

    boost::asio::async_read(serial_c6657, boost::asio::buffer(*recv_buffer),
                            boost::bind(&C6657SerialPort::data_recieved, this,
                              boost::asio::placeholders::error,
                              boost::asio::placeholders::bytes_transferred) );

//    serial_c6657.async_read_some( boost::asio::buffer(recv_buffer),
//                                  boost::bind(&C6657SerialPort::data_recieved, this,
//                                    boost::asio::placeholders::error,
//                                    boost::asio::placeholders::bytes_transferred) );
}

void C6657SerialPort::data_recieved(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    Q_ASSERT( bytes_transferred == 5 );

    //received a completed frame.    
    processor->new_frame_arrived(recv_buffer,bytes_transferred);
    frames.free(recv_buffer);
    issue_async_read();
}


long C6657SerialPort::send(const char *data, size_t bytes)
{
    return serial_c6657.write_some( boost::asio::buffer(data,bytes) );
}


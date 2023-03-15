#ifndef C6657SERIALPORT_H
#define C6657SERIALPORT_H
#include <QObject>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/pool/object_pool.hpp>
#include "iioreceiver.h"
#include "serialincomingprocessor.h"


class IIncomingProcessor;
class C6657SerialPort : public QObject, public IIoReceiver, public IIoSender
{
    Q_OBJECT
public:
    typedef boost::array<char, 5> frame_type;
    explicit C6657SerialPort(boost::asio::io_context &io_context,
        IIncomingProcessor* p,
        QObject *parent = nullptr);
    ~C6657SerialPort();
    void issue_async_read();


    void data_recieved(const boost::system::error_code& error,std::size_t bytes_transferred);
    long send(const char *data, size_t bytes);
private:
    boost::asio::serial_port serial_c6657;
    IIncomingProcessor* processor;

protected:
    boost::object_pool<frame_type> frames;
    frame_type* recv_buffer;
};

#endif // C6657SERIALPORT_H

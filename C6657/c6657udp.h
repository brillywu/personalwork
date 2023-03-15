#ifndef C6657UDP_H
#define C6657UDP_H
#include <QObject>
#include "iioreceiver.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/pool/object_pool.hpp>


class IIncomingProcessor;

class C6657Udp : public QObject, IIoReceiver,public IIoSender
{
    Q_OBJECT
public:
    typedef boost::array<char, 1472> frame_type;

    explicit C6657Udp(boost::asio::io_context &io_context,
        IIncomingProcessor* p,
        QObject *parent = nullptr);
    void issue_async_read();
    long send(const char *data, size_t bytes);
protected:

    void data_recieved(const boost::system::error_code& error,std::size_t bytes_transferred);
private:
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint there;
private:
    IIncomingProcessor* processor;
protected:
    boost::object_pool<frame_type> frames;
    frame_type* recv_buffer;

};

#endif // C6657UDP_H

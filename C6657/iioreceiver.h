#ifndef IIORECEIVER_H
#define IIORECEIVER_H

#include <boost/asio.hpp>

class IIoReceiver
{
protected:
    boost::asio::io_context &io_context;
public:
    IIoReceiver(boost::asio::io_context &io_context);
    ~IIoReceiver();
    //first issue an async read,when data recieved, call data_recieved.
    virtual void issue_async_read()=0;
    virtual void data_recieved(const boost::system::error_code& error,std::size_t bytes_transferred)=0;

};

class IIoSender
{
public:
    virtual long send(const char* data,size_t bytes)=0;
};

#endif // IIORECEIVER_H

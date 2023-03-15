#ifndef UDPINCOMINGPROCESSOR_H
#define UDPINCOMINGPROCESSOR_H
#include "IncomingProcessor.h"
#include <cstdint>

class IIoLoger;
class UdpIncomingProcessor : public IIncomingProcessor
{

private:
    uint32_t current_data_id;
    uint32_t data[1024];
    uint32_t received_data_bytes;

    uint32_t current_img_id;
    uint16_t img[640*512];

    IIoLoger* loger;

public:
    UdpIncomingProcessor(IIoLoger* l);
    long new_frame_arrived(void* frame,size_t size);
};

#endif // UDPINCOMINGPROCESSOR_H

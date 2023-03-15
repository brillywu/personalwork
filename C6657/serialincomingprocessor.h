#ifndef SERIALINCOMINGPROCESSOR_H
#define SERIALINCOMINGPROCESSOR_H

#include "IncomingProcessor.h"


class IIoLoger;
class SerialIncomingProcessor : public IIncomingProcessor
{
private:
    IIoLoger* loger;
public:
    SerialIncomingProcessor(IIoLoger* l);
    long new_frame_arrived(void* frame,size_t size);
};

#endif // SERIALINCOMINGPROCESSOR_H

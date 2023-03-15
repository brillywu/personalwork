#ifndef INCOMINGPROCESSOR_H
#define INCOMINGPROCESSOR_H


class IIncomingProcessor {
public:
    virtual long new_frame_arrived(void* frame,size_t size)=0;
};


#endif // INCOMINGPROCESSOR_H

#include "serialincomingprocessor.h"
#include "IoLoger.h"
SerialIncomingProcessor::SerialIncomingProcessor(IIoLoger* l)
    :loger(l)
{

}

long SerialIncomingProcessor::new_frame_arrived(void *frame,size_t size)
{
    loger->chardump(true, (char*)frame, size);    
    return 0;
}

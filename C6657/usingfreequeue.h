#ifndef USINGFREEQUEUE_H
#define USINGFREEQUEUE_H
#include <list>

template <typename frame_type, typename queue_type>
class UsingFreeQueue {
public:
    static frame_type null;
protected:
    queue_type frame_queue;
    std::list<uint16_t> free_buffers;
    uint16_t using_buffers;

public:
    frame_type &get_free_one()
    {
        if( free_buffers.empty()) {
            return null;
        }

        int idx=free_buffers.front();
        free_buffers.pop_front();
        using_buffers=(idx);
        return frame_queue[idx];
    }

    void return_one(uint16_t return_idx)
    {
        free_buffers.push_back(return_idx);
    }
};

#endif // USINGFREEQUEUE_H

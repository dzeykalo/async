#include "async.h"
#include "owner.h"

namespace async {

handle_t connect(std::size_t bulk) 
{
    owner * ptr = new owner(bulk);
    return ptr;
}

void receive(handle_t _handle, const char *data, std::size_t size)
{
    owner *ptr = static_cast<owner*>(_handle);
    ptr->receive(data, size);
}

void disconnect(handle_t _handle) 
{
    owner *ptr = static_cast<owner*>(_handle);
    ptr->disconnect();
}

}
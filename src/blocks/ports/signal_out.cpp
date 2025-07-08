#include "blocks/internal/ports/signal_out.hpp"
#include "blocks/internal/ports/signal_in.hpp"

void MM::BlockPort::SignalOut::Send()
{
    if (auto sp = in.lock())
        sp->Receive(state); 
    state = false;
}
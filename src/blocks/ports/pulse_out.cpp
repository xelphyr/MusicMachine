#include "blocks/internal/ports/pulse_out.hpp"
#include "blocks/internal/ports/pulse_in.hpp"

void MM::BlockPort::PulseOut::Send()
{
    if (auto sp = in.lock())
        sp->Receive(state); 
    state = false;
}
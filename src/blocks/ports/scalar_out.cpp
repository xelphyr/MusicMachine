#include "blocks/internal/ports/scalar_out.hpp"
#include "blocks/internal/ports/scalar_in.hpp"

void MM::BlockPort::ScalarOut::Send()
{
    if (auto sp = in.lock())
        sp->Receive(state); 
    state = false;
}
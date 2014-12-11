#include "Pcv80.h"

namespace {
const unsigned int BIT_RW = 7;
const unsigned int BIT_ANF0 = 2;
const unsigned int BIT_ANF1 = 3;
const unsigned int BIT_ANF2 = 4;
const unsigned int BIT_ANF3 = 5;
const unsigned int BIT_ANF4 = 6;
}

Pcv80::Pcv80(Rs485& bus, const unsigned int id)
: _bus(bus),
    _id(id),
    _position(0.0f),
    _speed(0.0f)
{

}

void Pcv80::grab(void)
{
    std::vector<unsigned char> bytes(2);

    bytes[0] = ((1 << BIT_RW) | (1 << BIT_ANF1) | (_id & 0x3));
    bytes[1] = ~bytes[0];
    _bus.send(bytes);
    ::usleep(100);
    _bus.receive(bytes, 7);


    _position = 1e-4 * static_cast<float>((static_cast<unsigned int>(bytes[4]) <<  0) |
                                          (static_cast<unsigned int>(bytes[3]) <<  7) |
                                          (static_cast<unsigned int>(bytes[2]) << 14) |
                                          (static_cast<unsigned int>(bytes[1]) << 21));

    _speed = static_cast<float>(bytes[5]) * 0.1f;
}

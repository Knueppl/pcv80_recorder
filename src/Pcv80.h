#ifndef ___PCV_80_H___
#define ___PCV_80_H___

#include "Rs485.h"

class Pcv80
{
public:
    Pcv80(Rs485& bus, const unsigned int id);

    void grab(void);
    float position(void) const { return _position; }
    float speed(void) const { return _speed; }

private:
    Rs485& _bus;
    unsigned int _id;

    float _position;
    float _speed;
};

#endif

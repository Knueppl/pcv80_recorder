#ifndef ___RS485_H___
#define ___RS485_H___

#include <termios.h>
#include <unistd.h>
#include <vector>
#include <string>

class Rs485
{
public:

    enum Baud {
        BR0      = B0,
        BR50     = B50,
        BR75     = B75,
        BR110    = B110,
        BR134    = B134,
        BR150    = B150,
        BR200    = B200,
        BR300    = B300,
        BR600    = B600,
        BR1200   = B1200,
        BR1800   = B1800,
        BR2400   = B2400,
        BR4800   = B4800,
        BR9600   = B9600,
        BR19200  = B19200,
        BR38400  = B38400,
        BR57600  = B57600,
        BR115200 = B115200,
        BR230400 = B230400
    };

    Rs485(const std::string& device, const Baud baud = BR115200);
    ~Rs485(void);

    void send(const std::vector<unsigned char>& bytes);
    bool receive(std::vector<unsigned char>& data, const unsigned int bytes, const int timeout = -1);

private:
    int _fd;
    const unsigned int _bufferSize;
};

#endif

#include "Rs485.h"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

Rs485::Rs485(const std::string& device, const Baud baud)
: _bufferSize(1024)
{
    _fd = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

    if (_fd < 0)
    {
        std::cout << "Rs485: can't open device " << device << "." << std::endl;
        return;
    }

    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));

    if (tcgetattr(_fd, &tty))
    {
        std::cout << "Rs485: can't get the attributes from the device " << device << "." << std::endl;
        return;
    }

    cfsetospeed(&tty, static_cast<int>(baud));
    cfsetispeed(&tty, static_cast<int>(baud));

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag |= PARENB;
    tty.c_cflag &= ~PARODD;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag = 0;

    tty.c_iflag &= ~IGNBRK;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_oflag = 0;

    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(_fd, TCSANOW, &tty))
    {
        std::cout << "Rs485: can't set the attributes to the device " << device << "." << std::endl;
        return;
    }
}

Rs485::~Rs485(void)
{
    ::close(_fd);
}

void Rs485::send(const std::vector<unsigned char>& bytes)
{
    ::write(_fd, bytes.data(), bytes.size());
}

bool Rs485::receive(std::vector<unsigned char>& data, const unsigned int bytes, const int timeout)
{
    data.resize(bytes);

    int n = ::read(_fd, data.data(), data.size());

    return n == data.size();
}

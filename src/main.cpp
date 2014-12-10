#include "Rs485.h"

int main(int argc, char** argv)
{
    Rs485 bus("/dev/ttyS1", Rs485::BR115200);
}

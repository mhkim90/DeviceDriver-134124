#include "DeviceDriver.h"
#include <chrono>
#include <thread>
#include <exception>
#include <string>
using namespace std;

class ReadFailException : public exception {
public:
    ReadFailException(string msg) : exception{ msg.c_str()} {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int read_val = 0;
    for (int i = 0; i < num_of_repeat; i++) {
        if (i == 0) {
            read_val = (int)(m_hardware->read(address));
        }
        else if (read_val != (int)(m_hardware->read(address))) {
            throw ReadFailException("memory read failure");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
    return read_val;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}

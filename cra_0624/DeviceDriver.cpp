#include "DeviceDriver.h"
#include <chrono>
#include <thread>
#include <exception>
#include <string>
using namespace std;

static void doSleep(int sleep_time) {
    this_thread::sleep_for(chrono::milliseconds(sleep_time));
}

class ReadFailException : public exception {
public:
    ReadFailException(string msg) : exception{ msg.c_str()} {}
};

class WriteFailException : public exception {
public:
    WriteFailException(string msg) : exception{ msg.c_str() } {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int read_val = (int)(m_hardware->read(address));
    for (int i = 0; i < num_of_repeat - 1; i++) {
        doSleep(100);
        if (read_val != (int)(m_hardware->read(address))) {
            throw ReadFailException("memory read failure");
        }
    }
    return read_val;
}

void DeviceDriver::write(long address, int data)
{
    if (isMemoryEmpty(address)) {
        throw WriteFailException("memory write failure");
    }
    m_hardware->write(address, (unsigned char)data);
}

bool DeviceDriver::isMemoryEmpty(long address) {
    return m_hardware->read(address) != 0xFF;
}
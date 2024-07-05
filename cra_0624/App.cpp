#include "DeviceDriver.h"
#include <exception>
#include <string>
#include <iostream>
using namespace std;

class App {
public:
	App(DeviceDriver* driver) : m_driver{ driver } {}

	void ReadAndPrint(long startAddr, long endAddr) {
		for (long addr = startAddr; addr < endAddr; addr++) {
			cout << m_driver->read(addr) << endl;
		}
	}

	void WriteAll(int val) {
		for (long addr = 0x00; addr < 0x04; addr++) {
			m_driver->write(addr, val);
		}
	}

private:
	DeviceDriver* m_driver;
};
#include "DeviceDriver.h"
#include <exception>
#include <string>
#include <iostream>
using namespace std;

class App {
public:
	App(DeviceDriver* driver) : m_driver{ driver } {}

	void ReadAndPrint(long startAddr, long endAddr) {
		for (long addr = startAddr; addr <= endAddr; addr++) {
			cout << m_driver->read(addr) << endl;
		}
	}

	void WriteAll(int val) {
		for (long addr = m_startAddr; addr <= m_endAddr; addr++) {
			m_driver->write(addr, val);
		}
	}

private:
	DeviceDriver* m_driver;
	const long m_startAddr = 0x00;
	const long m_endAddr = 0x04;
};
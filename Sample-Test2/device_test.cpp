#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../cra_0624/DeviceDriver.cpp"
#include <string>
#include <vector>
#include <exception>
#include <ctime>
using namespace std;
using namespace testing;

class MockFMD : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class TestFixture : public ::testing::Test {
public:
	MockFMD fmd;
	DeviceDriver driver{ &fmd };

	const int num_repeat = 5;
protected:
	void SetUp() override {

	}
};

TEST_F(TestFixture, SameResult) {
	long addr = 0x00;
	EXPECT_CALL(fmd, read(addr))
		.Times(num_repeat)
		.WillRepeatedly(Return(1));
	for (int i = 0; i < num_repeat; i++) {
		driver.read(addr);
	}
}
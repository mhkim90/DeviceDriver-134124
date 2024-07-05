#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../cra_0624/DeviceDriver.cpp"
#include "../cra_0624/App.cpp"
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
	App app{ &driver };

	const int num_repeat = 5;
	const int read_val = 1;
	const int write_val = 2;
	const long addr = 0x00;
protected:
	void SetUp() override {

	}
};

TEST_F(TestFixture, ReadSucess) {
	EXPECT_CALL(fmd, read(addr))
		.Times(num_repeat)
		.WillRepeatedly(Return(read_val));
	EXPECT_EQ(driver.read(addr), read_val);
}

TEST_F(TestFixture, ReadFail) {
	EXPECT_CALL(fmd, read(addr))
		.Times(2)
		.WillOnce(Return(read_val))
		.WillOnce(Return(read_val + 1));
	EXPECT_THROW(driver.read(addr), ReadFailException);
}

TEST_F(TestFixture, WriteSucess) {
	EXPECT_CALL(fmd, read(addr))
		.Times(1)
		.WillOnce(Return(0xFF));
	EXPECT_CALL(fmd, write(addr, write_val))
		.Times(1);
	driver.write(addr, write_val);
}

TEST_F(TestFixture, WriteFail) {
	EXPECT_CALL(fmd, read(addr))
		.Times(1)
		.WillOnce(Return(read_val));
	EXPECT_CALL(fmd, write(addr, write_val))
		.Times(0);
	EXPECT_THROW(driver.write(addr, write_val), WriteFailException);
}
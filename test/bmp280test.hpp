#include <hwlib.hpp>

constexpr uint8_t BMP280_ADDRESS = 0x76;
constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

struct CalibrationData {
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    // Add other calibration data members as needed
};


class BMP280 {
private:
    hwlib::i2c_bus& bus;
    CalibrationData calibrationData; // Add the appropriate calibration data members

public:
    BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

    void writeRegister(uint8_t reg, uint8_t value);

    float readTemperature();

    void writeI2C();
};


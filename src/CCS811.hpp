#ifndef CCS811_HPP
#define CCS811_HPP

#include <hwlib.hpp>

class CCS811 {
private:
    hwlib::i2c_primitives& i2c;
    static constexpr uint8_t CCS811_ADDR = 0x5A;

public:
    CCS811(hwlib::i2c_primitives& i2c);
    void writeCommand(uint8_t command, uint8_t* data, size_t size);
    uint16_t readValue(uint8_t command, uint8_t* data, size_t size);
    bool readStatus();
    void init();
    uint16_t getCO2();
    uint16_t getTVOC();
};

#endif // CCS811_HPP

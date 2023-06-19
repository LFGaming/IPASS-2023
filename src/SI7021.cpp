#include "SI7021.hpp"

void SI7021::print(){
    hwlib::cout << "test";
}

void SI7021::I2C() {
    uint8_t temperature_out[2];

    // Create I2C write transaction
    { hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus*)(&bus)) -> write(0x40);
    writetrans.write (0xE3); }
    { hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus*)(&bus)) -> read(0x40);
    readtrans.read (temperature_out, 2); }

    // Calculate temperature from the received data
    uint16_t raw_temperature = (temperature_out[0] << 8) | temperature_out[1];
    // float temperature = static_cast<float>(raw_temperature) * 175.72 / 65536 - 46.85;
    uint16_t temperature = static_cast<float>(raw_temperature) * 175.72 / 65536 - 46.85;

    // Print the measured temperature
    hwlib::cout << "Temperature: " << temperature << " degrees Celsius" << hwlib::endl;
}
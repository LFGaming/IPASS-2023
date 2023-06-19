#include "SI7021.hpp"

void SI7021::GetTemperature() {
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

void SI7021::GetHumidity() {
    uint8_t humidity_out[2];

    // Create I2C write transaction
    { hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus*)(&bus)) -> write(0x40);
    writetrans.write (0xE5); }
    { hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus*)(&bus)) -> read(0x40);
    readtrans.read (humidity_out, 2); }

    // Calculate temperature from the received data
    uint16_t raw_humidity = (humidity_out[0] << 8) | humidity_out[1];
    // float temperature = static_cast<float>(raw_temperature) * 175.72 / 65536 - 46.85;
    uint16_t humidity = static_cast<float>(raw_humidity) * 125 / 65536 - 6;

    // Print the measured temperature
    hwlib::cout << "Humidity: " << humidity << "%" << hwlib::endl;
}
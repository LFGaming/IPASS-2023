/**
 * @file SI7021.cpp
 * @author Luke Tenback (Luke.tenback@student.hu.nl)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SI7021.hpp"

/**
 * @brief
 * Get the Temperature object
 * @details
 * Get the temperature data from the SI7021 sensor and convert that into usable degrees Celsius.
 */
int SI7021::GetTemperature() {
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
    return temperature;
    // Print the measured temperature
    // hwlib::cout << "Temperature: " << temperature << " degrees Celsius" << hwlib::endl;
}

/**
 * @brief 
 * Get the Humidity object
 * @details 
 * Get the humidity data from the SI7021 sensor and convert that into usable humidity percentages.
 */
int SI7021::GetHumidity() {
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
    return humidity;
    // Print the measured temperature
    hwlib::cout << "Humidity: " << humidity << "%" << hwlib::endl;
}
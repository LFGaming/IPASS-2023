#include "CCS811.hpp"

CCS811::CCS811(hwlib::i2c_primitives& i2c) : i2c(i2c) {}

void CCS811::writeCommand(uint8_t command, uint8_t* data, size_t size) {
    uint8_t buffer[5];
    buffer[0] = CCS811::CCS811_ADDR << 1;  // Shift address to the left by 1
    buffer[1] = command;

    for (size_t i = 0; i < size; i++) {
        buffer[i + 2] = data[i];
    }

    i2c.write(buffer, size + 2);
}

bool CCS811::readStatus() {
    uint8_t statusRegister = 0x00;
    i2c.write(CCS811::CCS811_ADDR);
    i2c.write(statusRegister);

    uint8_t status;
    i2c.read(true, &status, 1);

    // Check if the sensor is in an error state
    return ((status & 0x01) == 0x00);
}

void CCS811::init() {
    // Initialize CCS811 sensor
    uint8_t buffer[1] = { 0x10 }; // Mode 1: Constant Power Mode with 1 sec between readings
    writeCommand(0x01, buffer, 1);

    // Wait for the sensor to be ready (timeout after 5 seconds)
    unsigned long startTime = hwlib::now_us();
    while (!readStatus()) {
        // Check timeout
        if (hwlib::now_us() - startTime > 5'000'000) {
            // Timeout occurred, exit the loop
            break;
        }
        hwlib::wait_ms(100); // Delay for 100 milliseconds
    }
}

uint16_t CCS811::readValue(uint8_t command, uint8_t* data, size_t size) {
    i2c.write(CCS811::CCS811_ADDR);
    i2c.write(command);
    i2c.write(CCS811::CCS811_ADDR | 0x01); // Start read mode
    i2c.read(true, data, size);
    // Assuming that the data returned is a 16-bit value
    return (data[0] << 8) | data[1];
}

uint16_t CCS811::getCO2() {
    uint8_t data[2];
    return readValue(0x02, data, 2);
}

uint16_t CCS811::getTVOC() {
    uint8_t data[2];
    return readValue(0x03, data, 2);
}

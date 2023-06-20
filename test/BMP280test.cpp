// #include <iostream>
// #include <hwlib.hpp>

// // BMP280 register addresses
// #define BMP280_ADDRESS 0x76
// #define BMP280_REG_CONTROL 0xF4
// #define BMP280_REG_TEMP_MSB 0xFA
// #define BMP280_REG_TEMP_LSB 0xFB

// void writeRegister(hwlib::i2c_bus_bit_banged_scl_sda& bus, uint8_t reg, uint8_t value) {
//     bus.write(BMP280_ADDRESS).write(reg).write(value);
// }

// int16_t readTemperature(hwlib::i2c_bus_bit_banged_scl_sda& bus) {
//     bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//     uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
//     uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();
//     return (msb << 8) | lsb;
// }

// int main() {
//     // Initialize I2C communication
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    
//     // Configure BMP280 for temperature measurement
//     writeRegister(i2c_bus, BMP280_REG_CONTROL, 0x2E);
    
//     // Read temperature data
//     int16_t tempRaw = readTemperature(i2c_bus);
//     double temperature = (double)tempRaw / 100.0;
    
//     // Print the temperature value
//     hwlib::cout << "Temperature: " << temperature << " °C" << hwlib::endl;
    
//     return 0;
// }


// ##################################################### //


// #include <iostream>
// #include <hwlib.hpp>

// constexpr uint8_t BMP280_ADDRESS = 0x76;
// constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

// struct CalibrationData {
    //! Add the necessary calibration data members here
    /*
TODO    The calibration data for the BMP280 sensor is specific to each device and is typically stored in the sensor's non-volatile memory during manufacturing. The calibration data is used in the temperature and pressure calculations to obtain accurate readings from the sensor.
TODO
TODO    To retrieve the calibration data for your BMP280 sensor, you can follow these steps:
TODO
TODO    1. Refer to the BMP280 datasheet or the sensor manufacturer's documentation to understand the structure of the calibration data and its respective registers.
TODO    2. Use the I2C communication protocol to read the calibration data registers from the BMP280 sensor.
TODO    3. The calibration data consists of various coefficients, such as dig_T1, dig_T2, dig_T3, and others. These coefficients are typically 16-bit or 20-bit unsigned integers. The number and size of the coefficients depend on the sensor model.
TODO    4. Once you have read the calibration data from the sensor, store it in a suitable data structure or variables in your code.
TODO    5. Use the stored calibration data in your temperature and pressure calculations to obtain accurate readings from the BMP280 sensor.
TODO    
TODO    The specific method to read the calibration data may vary depending on the I2C library or framework you are using. Typically, you will need to perform I2C write and read operations to access the calibration data registers.
TODO
TODO    Consulting the BMP280 datasheet or the sensor manufacturer's documentation will provide detailed information on the calibration data structure, register addresses, and the procedure to read the calibration data from the sensor.
    */

// };

// class BMP280 {
// private:
//     hwlib::i2c_bus& bus;
//     CalibrationData calibrationData; // Add the appropriate calibration data

// public:
//     BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

//     void writeRegister(uint8_t reg, uint8_t value) {
//         bus.write(BMP280_ADDRESS).write(reg);
//         bus.write(value);
//     }

//     float readTemperature() {
//         bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//         hwlib::i2c_read_transaction readTransaction = bus.read(BMP280_ADDRESS);
//         uint8_t msb = readTransaction.read_byte();
//         readTransaction = bus.read(BMP280_ADDRESS);
//         uint8_t lsb = readTransaction.read_byte();

//         int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
//         int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
//                        (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
//         int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
//                           ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
//                         (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
//         int32_t t_fine = var1 + var2;
//         float T = (t_fine * 5 + 128) >> 8;
//         return T / 100.0f;
//     }
// };

// int main() {
//     // Initialize I2C pins
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

//     // Create BMP280 object
//     BMP280 bmp280(i2c_bus);

//     // Write a value to a register
//     bmp280.writeRegister(0x80, 0xFF);

//     // Read temperature
//     float temperature = bmp280.readTemperature();
//     hwlib::cout << "Temperature: " << temperature << " degrees Celsius\n";

//     return 0;
// }

// ################################ //

// #include <hwlib.hpp>

// constexpr uint8_t BMP280_ADDRESS = 0x76;
// constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

// struct CalibrationData {
//     uint16_t dig_T1;
//     int16_t dig_T2;
//     int16_t dig_T3;
//     // Add other calibration data members as needed
// };

// class BMP280 {
// private:
//     hwlib::i2c_bus& bus;
//     CalibrationData calibrationData; // Add the appropriate calibration data members

// public:
//     BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

//     void writeRegister(uint8_t reg, uint8_t value) {
//         bus.write(BMP280_ADDRESS).write(reg);
//         bus.write(value);
//     }

//     float readTemperature() {
//         bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//         hwlib::i2c_read_transaction readTransaction = bus.read(BMP280_ADDRESS);
//         uint8_t msb = readTransaction.read_byte();
//         readTransaction = bus.read(BMP280_ADDRESS);
//         uint8_t lsb = readTransaction.read_byte();

//         int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
//         int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
//                        (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
//         int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
//                           ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
//                         (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
//         int32_t t_fine = var1 + var2;
//         float T = (t_fine * 5 + 128) >> 8;
//         return T / 100.0f;
//     }
// };

// int main() {
//     // Initialize I2C pins
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

//     // Create BMP280 object
//     BMP280 bmp280(i2c_bus);

//     // Write a value to a register
//     bmp280.writeRegister(0x80, 0xFF);

//     // Read temperature
//     float temperature = bmp280.readTemperature();
//     hwlib::cout << "Temperature: " << temperature << " degrees Celsius\n";

//     return 0;
// }


// ################################ //

// #include <hwlib.hpp>

// constexpr uint8_t BMP280_ADDRESS = 0x76;
// constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

// struct CalibrationData {
//     uint16_t dig_T1;
//     int16_t dig_T2;
//     int16_t dig_T3;
//     // Add other calibration data members as needed
// };

// class BMP280 {
// private:
//     hwlib::i2c_bus& bus;
//     CalibrationData calibrationData; // Add the appropriate calibration data members

// public:
//     BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

//     void writeRegister(uint8_t reg, uint8_t value) {
//         bus.write(BMP280_ADDRESS).write(reg);
//         bus.write(value);
//     }

//     float readTemperature() {
//         bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//         uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
//         uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();

//         int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
//         int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
//                        (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
//         int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
//                           ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
//                         (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
//         int32_t t_fine = var1 + var2;
//         float T = (t_fine * 5 + 128) >> 8;
//         return T / 100.0f;
//     }
// };

// int main() {
//     // Initialize I2C pins
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

//     // Create BMP280 object
//     BMP280 bmp280(i2c_bus);

//     // Write a value to a register
//     bmp280.writeRegister(0x80, 0xFF);

//     // Read temperature
//     // float temperature = bmp280.readTemperature();
//     int temperature = bmp280.readTemperature();

//     hwlib::cout << "Temperature: " << temperature << " degrees Celsius\n";

//     return 0;
// }

// #################################### //

// #include <hwlib.hpp>
// #include "bmp280test.hpp"

// // constexpr uint8_t BMP280_ADDRESS = 0x76;
// // constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

// // struct CalibrationData {
// //     uint16_t dig_T1;
// //     int16_t dig_T2;
// //     int16_t dig_T3;
// //     // Add other calibration data members as needed
// // };

// void BMP280::writeRegister(uint8_t reg, uint8_t value) {
//     bus.write(BMP280_ADDRESS).write(reg);
//     bus.write(value);
// }

// float BMP280::readTemperature() {
//     bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//     uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
//     uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();

//     int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
//     int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
//                     (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
//     int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
//                         ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
//                     (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
//     int32_t t_fine = var1 + var2;
//     float T = (t_fine * 5 + 128) >> 8;
//     return T / 100.0f;
// }

// void BMP280::writeI2C() {
//     // Initialize I2C pins
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

//     // Create BMP280 object
//     BMP280 bmp280(i2c_bus);

//     // Write a value to a register
//     bmp280.writeRegister(0x80, 0xFF);

//     // Read temperature
//     // float temperature = bmp280.readTemperature();
//     int temperature = bmp280.readTemperature();

//     hwlib::cout << "Temperature: " << temperature << " degrees Celsius\n";
// }

// ############################# //

// #include <hwlib.hpp>

// constexpr uint8_t BMP280_ADDRESS = 0x76;
// constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

// struct CalibrationData {
//     // Add the necessary calibration data members here
// };

// class BMP280 {
// private:
//     hwlib::i2c_bus& bus;
//     CalibrationData calibrationData; // Add the appropriate calibration data

// public:
//     BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

//     void writeRegister(uint8_t reg, uint8_t value) {
//         bus.write(BMP280_ADDRESS).write(reg);
//         bus.write(value);
//     }

//     void writeI2C() {
//         // Write a value to a register
//         writeRegister(0x80, 0xFF);
//     }

//     float readTemperature() {
//         bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//         uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
//         uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();

//         int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
//         int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
//                        (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
//         int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
//                           ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
//                         (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
//         int32_t t_fine = var1 + var2;
//         float T = (t_fine * 5 + 128) >> 8;
//         return T / 100.0f;
//     }
// };

// ########################## //

// #include <hwlib.hpp>

// constexpr uint8_t BMP280_ADDRESS = 0x76;
// constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

// struct CalibrationData {
//     auto reg_data = read_registers(0x88, 24);
//     uint16_t dig_T1 = (reg_data->at(1) << 8) | reg_data->at(0);
//     int16_t dig_T2 = (reg_data->at(3) << 8) | reg_data->at(2);
//     int16_t dig_T3 = (reg_data->at(5) << 8) | reg_data->at(4);
//     uint16_t dig_P1 = (reg_data->at(7) << 8) | reg_data->at(6);
//     int16_t dig_P2 = (reg_data->at(9) << 8) | reg_data->at(8);
//     int16_t dig_P3 = (reg_data->at(11) << 8) | reg_data->at(10);
//     int16_t dig_P4 = (reg_data->at(13) << 8) | reg_data->at(12);
//     int16_t dig_P5 = (reg_data->at(15) << 8) | reg_data->at(14);
//     int16_t dig_P6 = (reg_data->at(17) << 8) | reg_data->at(16);
//     int16_t dig_P7 = (reg_data->at(19) << 8) | reg_data->at(18);
//     int16_t dig_P8 = (reg_data->at(21) << 8) | reg_data->at(20);
//     int16_t dig_P9 = (reg_data->at(23) << 8) | reg_data->at(22);
// };

// class BMP280 {
// private:
//     hwlib::i2c_bus& bus;
//     CalibrationData calibrationData;

// public:
//     BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

//     void writeRegister(uint8_t reg, uint8_t value) {
//         bus.write(BMP280_ADDRESS).write(reg);
//         bus.write(value);
//     }

//     void writeI2C() {
//         writeRegister(0x80, 0xFF);
//     }

//     float readTemperature() {
//         bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
//         uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
//         uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();

//         int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
//         int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
//                        (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
//         int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
//                           ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
//                         (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
//         int32_t t_fine = var1 + var2;
//         float T = (t_fine * 5 + 128) >> 8;
//         return T / 100.0f;
//     }
// };

// ####################### //

#include <hwlib.hpp>
#include <array>

constexpr uint8_t BMP280_ADDRESS = 0x77;
constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;

struct CalibrationData {
    uint16_t dig_T1; /**< dig_T1 cal register. */
    int16_t dig_T2;  /**<  dig_T2 cal register. */
    int16_t dig_T3;  /**< dig_T3 cal register. */

    uint16_t dig_P1; /**< dig_P1 cal register. */
    int16_t dig_P2;  /**< dig_P2 cal register. */
    int16_t dig_P3;  /**< dig_P3 cal register. */
    int16_t dig_P4;  /**< dig_P4 cal register. */
    int16_t dig_P5;  /**< dig_P5 cal register. */
    int16_t dig_P6;  /**< dig_P6 cal register. */
    int16_t dig_P7;  /**< dig_P7 cal register. */
    int16_t dig_P8;  /**< dig_P8 cal register. */
    int16_t dig_P9;  /**< dig_P9 cal register. */
};

class BMP280 {
private:
    hwlib::i2c_bus& bus;
    CalibrationData calibrationData; // Add the appropriate calibration data

public:
    BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

    void writeRegister(uint8_t reg, uint8_t value) {
        uint8_t data[] = {reg, value};
        bus.write(BMP280_ADDRESS).write(data, 2);
    }


    void writeI2C() {
        // Write a value to a register
        writeRegister(0x80, 0xFF);
    }

    std::array<uint8_t, 24> read_registers(uint8_t start, size_t count) {
        uint8_t data[] = { start };
        bus.write(BMP280_ADDRESS).write(data, 1);

        std::array<uint8_t, 24> buffer{};
        for (size_t i = 0; i < count; i++) {
            buffer[i] = bus.read(BMP280_ADDRESS).read_byte();
        }

        return buffer;
    }

    void read_calibration_data() {
        std::array<uint8_t, 24> reg_data = read_registers(0x88, 24);

        calibrationData.dig_T1 = (reg_data[0x88] << 8) | reg_data[0x89];
        calibrationData.dig_T2 = (reg_data[0x8A] << 8) | reg_data[0x8B];
        calibrationData.dig_T3 = (reg_data[0x8C] << 8) | reg_data[0x8D];
        calibrationData.dig_P1 = (reg_data[0x8E] << 8) | reg_data[0x8F];
        calibrationData.dig_P2 = (reg_data[0x90] << 8) | reg_data[0x91];
        calibrationData.dig_P3 = (reg_data[0x92] << 8) | reg_data[0x93];
        calibrationData.dig_P4 = (reg_data[0x94] << 8) | reg_data[0x95];
        calibrationData.dig_P5 = (reg_data[0x96] << 8) | reg_data[0x97];
        calibrationData.dig_P6 = (reg_data[0x98] << 8) | reg_data[0x99];
        calibrationData.dig_P7 = (reg_data[0x9A] << 8) | reg_data[0x9B];
        calibrationData.dig_P8 = (reg_data[0x9C] << 8) | reg_data[0x9D];
        calibrationData.dig_P9 = (reg_data[0x9E] << 8) | reg_data[0x9F];
    }

    float readTemperature() {
        bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);
        uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
        uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();

        int32_t adcValue = (static_cast<int32_t>(msb) << 12) | (static_cast<int32_t>(lsb) << 4);
        int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
            (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
        int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
            ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
            (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
        int32_t t_fine = var1 + var2;
        float T = (t_fine * 5 + 128) >> 8;
        return T / 100.0f;
    }
};
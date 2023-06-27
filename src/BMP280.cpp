/**
 * @file BMP280.cpp
 * @author Luke Tenback (Luke.tenback@student.hu.nl)
 * @brief 
 * @version 0.1
 * @date 2023-06-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "BMP280.hpp"
#include "SI7021.hpp"
#include <hwlib.hpp>
#include <array>

void BMP280::writeRegister() {
    uint8_t data[] = {0x80, 0xFF};
    bus.write(BMP280_ADDRESS).write(data, 2);
}

    // std::array<uint8_t, 24> BMP280::read_registers(uint8_t start, size_t count) {
    //     uint8_t data[] = { start };
    //     bus.write(BMP280_ADDRESS).write(data, 1);

    //     std::array<uint8_t, 24> buffer{};
    //     for (size_t i = 0; i < count; i++) {
    //         buffer[i] = bus.read(BMP280_ADDRESS).read_byte();
    //     }

    //     return buffer;
    // }

void BMP280::read_calibration_data() {
    std::array<uint8_t, 24> reg_data = read_registers(0x88, 24);

    // calibrationData.dig_T1 = (reg_data[0x88] << 8) | reg_data[0x89];
    // calibrationData.dig_T2 = (reg_data[0x8A] << 8) | reg_data[0x8B];
    // calibrationData.dig_T3 = (reg_data[0x8C] << 8) | reg_data[0x8D];
    // calibrationData.dig_P1 = (reg_data[0x8E] << 8) | reg_data[0x8F];
    // calibrationData.dig_P2 = (reg_data[0x90] << 8) | reg_data[0x91];
    // calibrationData.dig_P3 = (reg_data[0x92] << 8) | reg_data[0x93];
    // calibrationData.dig_P4 = (reg_data[0x94] << 8) | reg_data[0x95];
    // calibrationData.dig_P5 = (reg_data[0x96] << 8) | reg_data[0x97];
    // calibrationData.dig_P6 = (reg_data[0x98] << 8) | reg_data[0x99];
    // calibrationData.dig_P7 = (reg_data[0x9A] << 8) | reg_data[0x9B];
    // calibrationData.dig_P8 = (reg_data[0x9C] << 8) | reg_data[0x9D];
    // calibrationData.dig_P9 = (reg_data[0x9E] << 8) | reg_data[0x9F];
    calibrationData.dig_T1 = (reg_data[0x89] << 8) | reg_data[0x88];
    calibrationData.dig_T2 = (reg_data[0x8B] << 8) | reg_data[0x8A];
    calibrationData.dig_T3 = (reg_data[0x8D] << 8) | reg_data[0x8C];
    calibrationData.dig_P1 = (reg_data[0x8F] << 8) | reg_data[0x8E];
    calibrationData.dig_P2 = (reg_data[0x91] << 8) | reg_data[0x90];
    calibrationData.dig_P3 = (reg_data[0x93] << 8) | reg_data[0x92];
    calibrationData.dig_P4 = (reg_data[0x95] << 8) | reg_data[0x94];
    calibrationData.dig_P5 = (reg_data[0x97] << 8) | reg_data[0x96];
    calibrationData.dig_P6 = (reg_data[0x99] << 8) | reg_data[0x98];
    calibrationData.dig_P7 = (reg_data[0x9B] << 8) | reg_data[0x9A];
    calibrationData.dig_P8 = (reg_data[0x9D] << 8) | reg_data[0x9C];
    calibrationData.dig_P9 = (reg_data[0x9F] << 8) | reg_data[0x9E];
}

void BMP280::initialize() {
    // Perform the necessary initialization steps for BMP280 sensor
    // ...

    // config to add filter and standby timer
    { hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(&bus))->write(BMP280_ADDRESS);
    wtrans.write(config);
    wtrans.write(config_byte);}
    

    
    { hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(&bus))->write(BMP280_ADDRESS);
    wtrans.write(ctrl_hum);
    wtrans.write(osrs_h);}

    // Set the isInitialized flag to true
    isInitialized = true;
}
    long signed int t_fine;
float BMP280::readTemperature() {
    // bus.write(BMP280_ADDRESS).write(BMP280_REG_TEMP_MSB);

    uint8_t buffer[3];
    // bus.read(BMP280_ADDRESS).read(buffer, 3);

    { hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus*)(&bus)) -> write(BMP280_ADDRESS);
    writetrans.write (BMP280_REG_TEMP_MSB); }
    { hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus*)(&bus)) -> read(BMP280_ADDRESS);
    readtrans.read (buffer, 3); }
    uint32_t msb = buffer[0];
    uint32_t lsb = buffer[1];
    uint32_t xlsb = buffer[2];    

 hwlib::cout << buffer[0] << "\n" << hwlib::flush;
 hwlib::cout << buffer[1] << "\n" << hwlib::flush;
 hwlib::cout << calibrationData.dig_T1 << "\n" << hwlib::flush;


    // uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
    // uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();
    xlsb >>= 4;
    int32_t adcValue = (msb << 8) | (lsb << 4) | (xlsb);
    // int32_t var1 = ((((adcValue >> 3) - (static_cast<int32_t>(calibrationData.dig_T1) << 1))) *
    //     (static_cast<int32_t>(calibrationData.dig_T2))) >> 11;
    // int32_t var2 = (((((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1))) *
    //     ((adcValue >> 4) - (static_cast<int32_t>(calibrationData.dig_T1)))) >> 12) *
    //     (static_cast<int32_t>(calibrationData.dig_T3))) >> 14;
    // int32_t t_fine = var1 + var2;
    // float T = (t_fine * 5 + 128) >> 8;
    // return T / 100.0f;
    

        long signed int var1, var2, T;
        var1 = ((((adcValue>>3) - ((long signed int)calibrationData.dig_T1<<1))) * ((long signed int)calibrationData.dig_T2)) >> 11;
        var2 = (((((adcValue>>4) - ((long signed int)calibrationData.dig_T1)) * ((adcValue>>4) - ((long signed int)calibrationData.dig_T1))) >> 12) *
        ((long signed int)calibrationData.dig_T3)) >> 14;
        t_fine = var1 + var2;
        T = (t_fine * 5 + 128) >> 8;
        return T;
}

float BMP280::readPressure() {
    int64_t var1, var2, p;
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    SI7021 si7021(scl, sda);


    // Must be done first to get the t_fine variable set up
    int32_t t_fine = si7021.GetTemperature();

    bus.write(BMP280_ADDRESS).write(BMP280_REGISTER_PRESSUREDATA); // Register address for pressure data
    uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
    uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();
    uint8_t xlsb = bus.read(BMP280_ADDRESS).read_byte();

    int32_t adc_P = (static_cast<int32_t>(msb) << 16) | (static_cast<int32_t>(lsb) << 8) | (static_cast<int32_t>(xlsb) >> 4);
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * calibrationData.dig_P6 / 0x100000000;
    var2 = var2 + ((var1 * calibrationData.dig_P5) << 17);
    var2 = var2 + (static_cast<int64_t>(calibrationData.dig_P4) << 35);
    var1 = ((var1 * var1 * calibrationData.dig_P3) >> 8) + ((var1 * calibrationData.dig_P2) << 12);
    var1 = ((((int64_t)1) << 47) + var1) * calibrationData.dig_P1 >> 33;

    if (var1 == 0) {
        return 0; // avoid exception caused by division by zero
    }

    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = ((static_cast<int64_t>(calibrationData.dig_P9) * (p >> 13) * (p >> 13)) >> 25);
    var2 = ((static_cast<int64_t>(calibrationData.dig_P8) * p) >> 19);
    p = ((p + var1 + var2) >> 8) + (static_cast<int64_t>(calibrationData.dig_P7) << 4);

    return static_cast<float>(p) / 256.0f;
}




// float BMP280::readPressure() {
// 	int64_t var1, var2, p;
//     int32_t t_fine = readTemperature();
//         bus.write(BMP280_ADDRESS).write(BMP280_REGISTER_PRESSUREDATA); // Register address for pressure data
//     uint8_t msb = bus.read(BMP280_ADDRESS).read_byte();
//     uint8_t lsb = bus.read(BMP280_ADDRESS).read_byte();
//     uint8_t xlsb = bus.read(BMP280_ADDRESS).read_byte();

//     int32_t adcValue = (static_cast<int32_t>(msb) << 16) | (static_cast<int32_t>(lsb) << 8) | (static_cast<int32_t>(xlsb) >> 4);

// 	var1 = static_cast<int64_t>(t_fine) - 128000;
// 	var2 = var1 * var1 * (int64_t) calibrationData.dig_P6;
// 	var2 = var2 + ((var1 * (int64_t) calibrationData.dig_P5) << 17);
// 	var2 = var2 + (((int64_t) calibrationData.dig_P4) << 35);
// 	var1 = ((var1 * var1 * (int64_t) calibrationData.dig_P3) >> 8)
// 			+ ((var1 * (int64_t) calibrationData.dig_P2) << 12);
// 	var1 = (((int64_t) 1 << 47) + var1) * ((int64_t) calibrationData.dig_P1) >> 33;

// 	if (var1 == 0) {
// 		return 0;  // avoid exception caused by division by zero
// 	}

// 	p = 1048576 - adcValue;
// 	p = (((p << 31) - var2) * 3125) / var1;
// 	var1 = ((int64_t) calibrationData.dig_P9 * (p >> 13) * (p >> 13)) >> 25;
// 	var2 = ((int64_t) calibrationData.dig_P8 * p) >> 19;

// 	p = ((p + var1 + var2) >> 8) + ((int64_t) calibrationData.dig_P7 << 4);
// 	return p;
// }

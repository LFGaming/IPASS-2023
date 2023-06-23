/**
 * @file BMP280.hpp
 * @author Luke Tenback (Luke.tenback@student.hu.nl)
 * @brief This file contains the declaration of the BMP280 class and related structures.
 * @details The BMP280 class provides functions to communicate with the BMP280 temperature and pressure sensor using I2C.
 *          It allows reading temperature and calibration data from the sensor.
 * @date 2023-06-23
 * @version 0.1
 *
 */

#ifndef BMP280_HPP
#define BMP280_HPP

#include <hwlib.hpp>
#include <array>

constexpr uint8_t BMP280_ADDRESS = 0x77; /**< I2C address of the BMP280 sensor. */
constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA; /**< Register address for temperature MSB. */

/**
 * @struct CalibrationData
 * @brief Structure to store calibration data of the BMP280 sensor.
 */
struct CalibrationData {
    uint16_t dig_T1; /**< Calibration register for dig_T1. */
    int16_t dig_T2;  /**< Calibration register for dig_T2. */
    int16_t dig_T3;  /**< Calibration register for dig_T3. */

    uint16_t dig_P1; /**< Calibration register for dig_P1. */
    int16_t dig_P2;  /**< Calibration register for dig_P2. */
    int16_t dig_P3;  /**< Calibration register for dig_P3. */
    int16_t dig_P4;  /**< Calibration register for dig_P4. */
    int16_t dig_P5;  /**< Calibration register for dig_P5. */
    int16_t dig_P6;  /**< Calibration register for dig_P6. */
    int16_t dig_P7;  /**< Calibration register for dig_P7. */
    int16_t dig_P8;  /**< Calibration register for dig_P8. */
    int16_t dig_P9;  /**< Calibration register for dig_P9. */
};

/**
 * @class BMP280
 * @brief Class for interfacing with the BMP280 temperature and pressure sensor.
 * @details The BMP280 class provides functions to communicate with the BMP280 sensor using I2C.
 *          It allows reading temperature and calibration data from the sensor.
 */
class BMP280 {
private:
    hwlib::i2c_bus& bus; /**< Reference to the I2C bus used for communication. */
    CalibrationData calibrationData; /**< Calibration data of the BMP280 sensor. */

public:
    /**
     * @brief Construct a new BMP280 object.
     *
     * @param bus The I2C bus to communicate with the BMP280 sensor.
     */
    BMP280(hwlib::i2c_bus& bus) : bus(bus) {}

    /**
     * @brief Write data to a register of the BMP280 sensor.
     * @details This function writes data to a specific register of the BMP280 sensor.
     */
    void writeRegister();

    /**
     * @brief Read a sequence of registers from the BMP280 sensor.
     * @details This function reads a sequence of registers from the BMP280 sensor.
     *
     * @param start The starting register address.
     * @param count The number of registers to read.
     * @return std::array<uint8_t, 24> The data read from the registers.
     */
    std::array<uint8_t, 24> read_registers(uint8_t start, size_t count);

    /**
     * @brief Read the calibration data from the BMP280 sensor.
     * @details This function reads the calibration data from the BMP280 sensor.
     */
    void read_calibration_data();

    /**
     * @brief Read the temperature from the BMP280 sensor.
     * @details This function reads the temperature from the BMP280 sensor and returns the value in degrees Celsius.
     *
     * @return float The temperature value in degrees Celsius.
     */
    float readTemperature();
};

#endif // BMP280_HPP

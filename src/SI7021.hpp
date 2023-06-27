/**
 * @file SI7021.hpp
 * @author Luke Tenback (Luke.tenback@student.hu.nl)
 * @brief This file contains the declaration of the SI7021 class for interfacing with the SI7021 sensor.
 * @date 2023-06-23
 * @version 0.1
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SI7021_HPP
#define SI7021_HPP

#include "hwlib.hpp"

/**
 * @class SI7021
 * @brief Class for interfacing with the SI7021 temperature and humidity sensor.
 * @details The SI7021 class provides functions to communicate with the SI7021 sensor using I2C.
 *          It allows reading temperature and humidity data from the sensor.
 */
class SI7021 {
private:
    hwlib::pin_oc& scl; /**< The SCL pin for I2C communication. */
    hwlib::pin_oc& sda; /**< The SDA pin for I2C communication. */
    hwlib::i2c_bus_bit_banged_scl_sda bus; /**< The I2C bus for communication. */

public:
    /**
     * @brief Construct a new SI7021 object.
     *
     * @param scl The SCL pin for I2C communication.
     * @param sda The SDA pin for I2C communication.
     */
    SI7021(hwlib::target::pin_oc& scl, hwlib::target::pin_oc& sda)
        : scl(scl), sda(sda), bus(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)) {}

    /**
     * @brief Get the temperature from the SI7021 sensor.
     * @details This function retrieves the temperature data from the SI7021 sensor and converts it into degrees Celsius.
     *
     * @return int The temperature value in degrees Celsius.
     */
    int GetTemperature();

    /**
     * @brief Get the humidity from the SI7021 sensor.
     * @details This function retrieves the humidity data from the SI7021 sensor and converts it into percentage.
     *
     * @return int The humidity value in percentage.
     */
    int GetHumidity();

    /**
     * @brief Test the SI7021 temperature measurement.
     * @details This function tests the temperature measurement functionality of the SI7021 sensor.
     * It prompts the user to verify the measured temperature and returns the user's input.
     *
     * @return int The user's input ('y' or 'n') indicating whether the measured temperature is correct or not.
     */
    int testTemp();

    /**
     * @brief Test the SI7021 humidity measurement.
     * @details This function tests the humidity measurement functionality of the SI7021 sensor.
     * It prompts the user to verify the measured humidity and returns the user's input.
     *
     * @return int The user's input ('y' or 'n') indicating whether the measured humidity is correct or not.
     */
    int testHumid();

    /**
     * @brief Perform a self-test of the SI7021 sensor.
     * @details This function performs a self-test of the SI7021 sensor by testing the temperature and humidity measurements.
     * It prompts the user to verify the measured values and returns a boolean indicating whether the self-test passed or not.
     *
     * @return bool True if the self-test passed, False otherwise.
     */
    bool SItest();
};

#endif // SI7021_HPP

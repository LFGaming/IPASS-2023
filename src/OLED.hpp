/**
 * @file OLED.hpp
 * @author Luke Tenback (Luke.tenback@student.hu.nl)
 * @brief This file contains the declaration of the OLED class for interfacing with the OLED display.
 * @date 2023-06-23
 * @version 0.1
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef OLED_HPP
#define OLED_HPP

#include "hwlib.hpp"

/**
 * @class OLED
 * @brief Class for interfacing with the OLED display.
 * @details The OLED class provides functions to communicate with the OLED display using I2C.
 *          It allows adding a header line, printing temperature and humidity values, and clearing the screen.
 */
class OLED {
private:
    hwlib::i2c_bus_bit_banged_scl_sda& bus; /**< The I2C bus for communication. */
    hwlib::glcd_oled oled; /**< The OLED display. */
    hwlib::font_default_8x8 font; /**< The default 8x8 font for the terminal. */
    hwlib::font_default_16x16 big_font; /**< The default 16x16 font for the big terminal. */
    hwlib::terminal_from header; /**< The terminal for the header. */
    hwlib::terminal_from big_header; /**< The terminal for the big header. */

public:
    /**
     * @brief Construct a new OLED object.
     *
     * @param bus The I2C bus for communication.
     * @param address The I2C address of the OLED display.
     */
    OLED(hwlib::i2c_bus_bit_banged_scl_sda& bus, uint8_t address)
        : bus(bus)
        , oled(hwlib::glcd_oled(bus, address))
        , font(hwlib::font_default_8x8())
        , big_font(hwlib::font_default_16x16())
        , header(hwlib::terminal_from(oled, font))
        , big_header(hwlib::terminal_from(oled, big_font))
    {}

    /**
     * @brief Add a header line.
     * @details Adds a line under the Big Header at the top of the screen.
     */
    void headerline();

    /**
     * @brief Print the values of the given parameters.
     * @details Prints the values of the temperature and humidity parameters on the screen.
     *
     * @param temperature The temperature value to print.
     * @param humidity The humidity value to print.
     */
    void print(int temperature, int humidity);

    /**
     * @brief Clear the OLED screen.
     * @details Clears the entire OLED screen so that it can be written on again.
     */
    void clear();
};

#endif // OLED_HPP

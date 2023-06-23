#ifndef OLED_HPP
#define OLED_HPP
#include "hwlib.hpp"

class OLED
{
    hwlib::i2c_bus_bit_banged_scl_sda & bus;
    hwlib::glcd_oled oled;
    hwlib::font_default_8x8 font;
    hwlib::font_default_16x16 big_font;
    hwlib::terminal_from header;
    hwlib::terminal_from big_header;
     
public:
   
   OLED(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t adress): 
    bus(bus),
    oled(hwlib::glcd_oled(bus, adress)),
    font(hwlib::font_default_8x8()),
    big_font(hwlib::font_default_16x16()),
    header(hwlib::terminal_from( oled, font )),
    big_header(hwlib::terminal_from( oled, big_font ))
    {}

    void headerline();

    void print(int temperature, int humidity);

    void clear();

};

#endif // OLED_HPP

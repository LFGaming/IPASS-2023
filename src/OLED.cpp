/**
 * @file OLED.cpp
 * @author Luke Tenback (Luke.tenback@student.hu.nl)
 * @brief 
 * @version 0.1
 * @date 2023-06-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "OLED.hpp"

void OLED::headerline(){
    for( int16_t i = 0; i < oled.size.x - 10; i++ ){
        oled.write( hwlib::xy( i, 15 ) );
    }
    oled.flush();
}

void OLED::print(int temperature, int humidity){
    big_header
        << "\f" << "SI7021";
    header
        << "\t0302" << temperature<< "C Degrees";
    header
        << "\t0304" << humidity<< "% Humidity";
    header
    << hwlib::flush;
    big_header
    << hwlib::flush;
   
}

void OLED::clear(){
    oled.clear();
    }

void OLED::OLEDtesttext(){
    big_header
        << "\f" << "SI7021";
    header
        << "\t0302" << "25"<< "C Degrees";
    header
        << "\t0304" << "50"<< "% Humidity";
    header
    << hwlib::flush;
    big_header
    << hwlib::flush;
}

bool OLED::OLEDtest(){
    char input;
    OLEDtesttext();
    headerline();

    hwlib::wait_ms(200);
    hwlib::cout
        << "you should see the following y/n\n"
        << "__________________________\n"
        << "|  SI7021                |\n"
        << "|________________________|\n"
        << "|    25C degrees         |\n"
        << "|    50% Humidity        |\n"
        << "|________________________|\n";

    hwlib::cin>>input;
    while (input != 'y' && input != 'n')
    {
        hwlib::cin>>input;
    }
    if (input == 'y')
    {
        return true;
    }else
    {
        hwlib::wait_ms(200);
        hwlib::cout<< "The Oled does not work or is not conencted properly... ";
        return false;
    }
}
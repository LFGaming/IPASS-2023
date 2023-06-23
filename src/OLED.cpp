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
        << "\t0302" << temperature<< "C degrees";
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

    
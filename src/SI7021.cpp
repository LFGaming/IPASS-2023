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

int SI7021::GetTemperature() {
    uint8_t temperature_out[2];

    // Create I2C write transaction
    { hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus*)(&bus)) -> write(0x40);
    writetrans.write (0xE3); }
    { hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus*)(&bus)) -> read(0x40);
    readtrans.read (temperature_out, 2); }

    // Calculate temperature from the received data
    uint16_t raw_temperature = (temperature_out[0] << 8) | temperature_out[1];
    uint16_t temperature = static_cast<float>(raw_temperature) * 175.72 / 65536 - 46.85;
    return temperature;
}

int SI7021::GetHumidity() {
    uint8_t humidity_out[2];

    // Create I2C write transaction
    { hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus*)(&bus)) -> write(0x40);
    writetrans.write (0xE5); }
    { hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus*)(&bus)) -> read(0x40);
    readtrans.read (humidity_out, 2); }

    // Calculate temperature from the received data
    uint16_t raw_humidity = (humidity_out[0] << 8) | humidity_out[1];
    uint16_t humidity = static_cast<float>(raw_humidity) * 125 / 65536 - 6;
    return humidity;
}

// ################################# //
// Tests for the the SI7021 sensor   //
// ################################# //

int SI7021::testTemp(){
    hwlib::wait_ms(1000);
    char input;
    hwlib::cout << "Testing the SI7021 Temperature:" << "\n" << hwlib::flush;
    int temperature = GetTemperature();
    hwlib::cout<<temperature << hwlib::endl;

    hwlib::cout<<"Does the above value seem correct? y/n "<< "\n" ;
    hwlib::cin>>input;
    while (input != 'y' && input != 'n')
    {
        hwlib::cin>>input;
    }
    return input;
}

int SI7021::testHumid(){
    hwlib::wait_ms(1000);
    char input;
    hwlib::cout << "Testing the SI7021 Humidity:" << "\n" << hwlib::flush;
    int temperature = GetHumidity();
    hwlib::cout<<temperature << hwlib::endl;

    hwlib::cout<<"Does the above value seem correct? y/n "<< "\n" ;
    hwlib::cin>>input;
    while (input != 'y' && input != 'n')
    {
        hwlib::cin>>input;
    }
    return input;
}

bool SI7021::SItest(){
    if(testTemp() == 'y'){
        hwlib::wait_ms(200);
        hwlib::cout<< "Temperature works correctly \n";
        if (testHumid() == 'y')
        {
            hwlib::wait_ms(200);
            hwlib::cout<< "Humidity works correctly \n";
            return true;
        }else
        {
            hwlib::wait_ms(200);
            hwlib::cout<< "Humidity does not works correctly... \n";
            return false;
        }
    }else
    {
        hwlib::wait_ms(200);
        hwlib::cout<< "Temperature does not work correctly... \n";
        return false;
    }
}
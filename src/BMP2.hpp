#ifndef BPMP280_HPP
#define BMP280_HPP

#define BMP280_S32_t long signed int

#include <hwlib.hpp>
#include <array>
    constexpr uint8_t BMP280_ADDRESS = 0x77;
    constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;
    constexpr uint8_t BMP280_REGISTER_PRESSUREDATA = 0xF7;
class BMP280 {
private:


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

   // int32_t t_fine; // Member variable for storing fine temperature value
    hwlib::pin_oc & scl;
    hwlib::pin_oc & sda;
    hwlib::i2c_bus_bit_banged_scl_sda bus;

public:
    BMP280(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda) :
    scl(scl),
    sda(sda),
    bus (hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ))
    {}

    void gettemp(){
        uint8_t temperature_out[3];

    { hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus*)(&bus)) -> write(BMP280_ADDRESS);
    writetrans.write (BMP280_REG_TEMP_MSB); }
    { hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus*)(&bus)) -> read(BMP280_ADDRESS);
    readtrans.read (temperature_out, 3); }



    	// hwlib::cout << temperature_out[0] << "\n" << hwlib::flush;
    	// hwlib::cout << temperature_out[1] << "\n" << hwlib::flush;
    	// hwlib::cout << temperature_out[2] << "\n" << hwlib::flush;

    //  { hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(bus))->write(address);
    // wtrans.write(temp_reg);}

    //   // read results from temperature adress in Celcius(C)
    // { hwlib::i2c_read_transaction rtrans = ((hwlib::i2c_bus*)(bus))->read(address);
    //     rtrans.read(results, 3);}
 
    int32_t raw_output = 0x000;
    temperature_out[2] >>= 4;
    raw_output = (raw_output|temperature_out[0]) << 8;
    raw_output = (raw_output|temperature_out[1]) <<4;
    raw_output = raw_output |temperature_out[2];
    
  // bmp280_compensate_T_int32(raw_output);
   hwlib::cout << "BMP280: Temperature: " << bmp280_compensate_T_int32(raw_output) << " degrees Celsius\n" <<  hwlib::flush;
}

    


BMP280_S32_t t_fine;
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T)
{
    BMP280_S32_t var1, var2, T;
    var1 = ((((adc_T>>3) - ((BMP280_S32_t)dig_T1<<1))) * ((BMP280_S32_t)dig_T2)) >> 11;
    var2 = (((((adc_T>>4) - ((BMP280_S32_t)dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)dig_T1))) >> 12) *
    ((BMP280_S32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

};

#endif //BMP280_HPP
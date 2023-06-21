#ifndef BPMP280_HPP
#define BMP280_HPP

#include <hwlib.hpp>
#include <array>

constexpr uint8_t BMP280_ADDRESS = 0x77;
constexpr uint8_t BMP280_REG_TEMP_MSB = 0xFA;
constexpr uint8_t BMP280_REGISTER_PRESSUREDATA = 0xF7;

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

    int32_t t_fine; // Member variable for storing fine temperature value
};

class BMP280 {
private:
    hwlib::pin_oc & scl;
    hwlib::pin_oc & sda;
    hwlib::i2c_bus& bus;
    CalibrationData calibrationData; // Add the appropriate calibration data

public:
    BMP280(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda, hwlib::i2c_bus& bus) :
    scl(scl),
    sda(sda),
    bus(bus)
    {}

    void write_start(){
        sda.write( 0 ); sda.flush();
        hwlib::wait_us(1);  
        scl.write( 0 ); scl.flush();
        hwlib::wait_us(1);  
    }
    
    void write_nack(){
        scl.write( 0 ); scl.flush();
        hwlib::wait_us(1);   
        sda.write( 1 ); sda.flush();
        hwlib::wait_us(1);
        scl.write( 1 ); scl.flush();
        hwlib::wait_us(1);
        scl.write( 0 ); scl.flush();
        hwlib::wait_us(1);   
        sda.write( 0 ); sda.flush();
        hwlib::wait_us(1);  
    }

    void write_stop(){
        scl.write( 0 ); scl.flush();
        hwlib::wait_us(1);  
        sda.write( 0 ); sda.flush();
        hwlib::wait_us(1);   
        scl.write( 1 ); scl.flush();
        hwlib::wait_us(1);   
        sda.write( 1 ); sda.flush();
        hwlib::wait_us(1);
    }

    void writeRegister();

    //fix that this works from within the cpp too.
    std::array<uint8_t, 24> read_registers(uint8_t start, size_t count) {
        uint8_t data[] = { start };
        bus.write(BMP280_ADDRESS).write(data, 1);

        std::array<uint8_t, 24> buffer{};
        for (size_t i = 0; i < count; i++) {
            buffer[i] = bus.read(BMP280_ADDRESS).read_byte();
        }

        return buffer;
    }

    void read_calibration_data();

    float readTemperature();

    float readPressure();

};

#endif //BMP280_HPP
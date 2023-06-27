#include "SI7021.hpp"
#include "OLED.hpp"
#include "CCS811.hpp"

int main(int argc, char const *argv[])
{
    bool ok = false;
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    // Create CCS811 sensor object
    CCS811 ccs811(i2c_bus);

    // Initialize CCS811 sensor
    ccs811.init();

    hwlib::cout << "I2C" << "\n" << hwlib::flush;
    // Call the I2C function
    if (si7021.SItest() && Oled.OLEDtest())
    {
        ok = true;
    }
    
    while (ok)
    {
            // Read CO2 and TVOC values
    uint16_t co2 = ccs811.getCO2();
    uint16_t tvoc = ccs811.getTVOC();

    // Print values
    hwlib::wait_ms(500);
    hwlib::cout << "CO2: " << co2 << " ppm" << hwlib::endl;
    hwlib::cout << "TVOC: " << tvoc << " ppb" << hwlib::endl;
    }


    return 0;
}

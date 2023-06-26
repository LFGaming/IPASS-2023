// #include "SI7021.hpp"
// #include "OLED.hpp"
// #include "CCS811.hpp"


// int main(int argc, char const *argv[])
// {
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     SI7021 si7021(scl, sda); // Create an instance of the SI7021 class
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

//     OLED Oled = OLED(i2c_bus, 0x3c);
//     CCS811 ccs811(i2c_bus);

//     ccs811.init();

//     // Wait for the PC console to start
//     hwlib::wait_ms(100);
//     Oled.clear();

//     hwlib::wait_ms(200);
//     hwlib::cout << "I2C" << "\n";
//     // Call the I2C function
//     while (true)
//     {
//         // SI7021
//         int temperature = si7021.GetTemperature();
//         int humidity = si7021.GetHumidity();
//         uint16_t co2 = ccs811.getCO2();
//         uint16_t tvoc = ccs811.getTVOC();
//         hwlib::wait_ms(200);
//         hwlib::cout << "CO2: " << co2 << " ppm" << hwlib::endl;
//         hwlib::cout << "TVOC: " << tvoc << " ppb" << hwlib::endl;
//         Oled.clear();
//         Oled.print(temperature, humidity);
//         Oled.headerline();
//         hwlib::wait_ms(10000);
//     }

//     return 0;
// }

#include "hwlib.hpp"
#include "CCS811.hpp"

int main() {
    // Initialize I2C bus
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    // Create CCS811 sensor object
    CCS811 ccs811(i2c_bus);

    // Initialize CCS811 sensor
    ccs811.init();

    while (true)
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

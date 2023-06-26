#include "SI7021.hpp"
#include "OLED.hpp"

int main(int argc, char const *argv[])
{
    bool ok = false;
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    SI7021 si7021(scl, sda); // Create an instance of the SI7021 class
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

   OLED Oled = OLED(i2c_bus, 0x3c);

    // Wait for the PC console to start
    hwlib::wait_ms(100);
    Oled.clear();

    hwlib::cout << "I2C" << "\n" << hwlib::flush;
    // Call the I2C function
    if (si7021.SItest() && Oled.OLEDtest())
    {
        ok = true;
    }
    
    while (ok)
    {
        // SI7021
        int temperature = si7021.GetTemperature();
        int humidity = si7021.GetHumidity();
        Oled.clear();
        Oled.print(temperature, humidity);
        Oled.headerline();
        hwlib::wait_ms(10000);
    }

    return 0;
}

#include "SI7021.hpp"

int main(int argc, char const *argv[])
{
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    SI7021 sensor(scl, sda); // Create an instance of the SI7021 class

    // Wait for the PC console to start
    hwlib::wait_ms(100);

    hwlib::cout << "I2C" << "\n" << hwlib::flush;
    // Call the I2C function
    while (true)
    {
        sensor.GetTemperature();
        sensor.GetHumidity();
        hwlib::wait_ms(10000);
    }

    return 0;
}

#include "SI7021.hpp"
#include "BMP280.hpp"

int main(int argc, char const *argv[])
{
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    SI7021 si7021(scl, sda); // Create an instance of the SI7021 class
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    // Create BMP280 object
    BMP280 bmp280(i2c_bus);

    // Read calibration data
    bmp280.read_calibration_data();

    // Wait for the PC console to start
    hwlib::wait_ms(100);

    hwlib::cout << "I2C" << "\n" << hwlib::flush;
    // Call the I2C function
    while (true)
    {
        // SI7021
        si7021.GetTemperature();
        si7021.GetHumidity();

        // BMP280
        // Read temperature
        float temperature = bmp280.readTemperature();

        // Convert float temperature to integer
        uint16_t temperatureInt = static_cast<uint16_t>(temperature);

        // Print temperature
        hwlib::cout << "BMP280: Temperature: " << temperatureInt << " degrees Celsius\n";

        hwlib::wait_ms(10000);
    }

    return 0;
}

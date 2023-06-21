#include "SI7021.hpp"
#include "BMP280.hpp"

int main(int argc, char const *argv[])
{
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    SI7021 si7021(scl, sda); // Create an instance of the SI7021 class
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    // Create BMP280 object
    BMP280 bmp280(scl, sda, i2c_bus);

    // Read calibration data
    bmp280.read_calibration_data();

    // Wait for the PC console to start
    hwlib::wait_ms(100);

    hwlib::cout << "I2C" << "\n" << hwlib::flush;
    // Call the I2C function
    while (true)
    {
        // SI7021
        // si7021.GetTemperature();
        // si7021.GetHumidity();

        // BMP280
        // Read temperature
        bmp280.readTemperature();
        // float temperature = bmp280.readTemperature();
        // //float temperature = 12.7;

        // // Convert float temperature to integer
        // //uint16_t temperatureInt = static_cast<uint16_t>(temperature);
        // int temperatureInt = static_cast<int>(temperature);

        // // Print temperature
        // hwlib::cout << "BMP280: Temperature: " << temperatureInt << " degrees Celsius\n";

        // hwlib::wait_ms(1000);
        // float temperature2 = bmp280.readTemperature();
        // //float temperature = 12.7;

        // // Convert float temperature to integer
        // //uint16_t temperatureInt2 = static_cast<uint16_t>(temperature2);
        // int temperatureInt2 = static_cast<int>(temperature2);

        // // Print temperature
        // hwlib::cout << "BMP280: Temperature2: " << temperatureInt2 << " degrees Celsius\n";

        //float pressure = bmp280.readPressure();
        // int pressureInt = pressure;
        //float pressure = 10.1;
        //uint16_t pressureInt = static_cast<uint16_t>(round(pressure));
        // int pressureInt = static_cast<int>(round(pressure));
        // uint32_t pressureInt = static_cast<uint32_t>(round(pressure));
        //hwlib::cout << "BMP280: Pressure " << pressureInt << " Pa \n";

        hwlib::wait_ms(10000);
    }

    return 0;
}

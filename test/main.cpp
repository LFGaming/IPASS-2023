#include "BMP280test.cpp"

int main()
{
    // Initialize I2C pins
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    // Create BMP280 object
    BMP280 bmp280(i2c_bus);

    // Call writeI2C() on the BMP280 object
    bmp280.writeI2C();

    // Read temperature
    float temperature = bmp280.readTemperature();

    // Convert float temperature to integer
    int temperatureInt = static_cast<int>(temperature);

    // Print temperature
    hwlib::cout << "Temperature: " << temperatureInt << " degrees Celsius\n";


    return 0;
}

#ifndef SI7021_HPP
#define SI7021_HPP

#include "hwlib.hpp"

class SI7021 {
    private:
    hwlib::pin_oc & scl;
    hwlib::pin_oc & sda;
    hwlib::i2c_bus_bit_banged_scl_sda bus;

    public:
    SI7021(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda):
    scl(scl),
    sda(sda),
    bus (hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ))
    {}

    void print();
    void GetTemperature();
    void GetHumidity();
};


#endif //SI7021_HPP
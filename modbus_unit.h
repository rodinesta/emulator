#pragma once

#include <iostream>
#include <string>
#include <vector>

struct reg {
    std::uint16_t address;
    std::string value;
    std::string dataType;
    std::string regType;
};

class modbus_unit {
    public:
        modbus_unit(std::uint8_t id, std::string protocol, std::string title);

        void display_info();
        void add_register(std::uint16_t address, const std::string& value, const std::string& dataType, const std::string& regType);

    private:
        std::uint16_t id;
        std::string protocol;
        std::string title;
        std::vector<reg> registers;
};
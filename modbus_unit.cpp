#include "modbus_unit.h"

modbus_unit::modbus_unit(std::uint8_t id, std::string protocol, std::string title) : id(id), protocol(protocol), title(title) {}

void modbus_unit::add_register(std::uint16_t address, const std::string& value, const std::string& dataType, const std::string& regType) {
    registers.push_back({address, value, dataType, regType});
}

void modbus_unit::display_info() {
    std::cout << "Device ID: " << id << std::endl;
    std::cout << "Protocol: " << protocol << std::endl;
    std::cout << "Title: " << title << std::endl;

    std::cout << "Registers:" << std::endl;
    for (const auto& reg : registers) {
        std::cout << "Address: " << reg.address << ", Value: " << reg.value << ", dataType: " 
        << reg.dataType <<  ", registerType: " <<  reg.regType << std::endl;
    }
}
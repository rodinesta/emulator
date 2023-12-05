#include <iostream>
#include <vector>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/http.h>
#include "tinyxml2.h"
#include "server.h"
#include "modbus_unit.h"

std::vector<modbus_unit *> units;

int main()
{
    tinyxml2::XMLDocument doc;
    // Получаем путь к файлу конфигурации
    std::filesystem::path currentPath = std::filesystem::current_path().parent_path();
    std::string confFilePath = currentPath.string() + "/conf.xml";
    doc.LoadFile(confFilePath.c_str());

    // Проверяем файл на целостность
    tinyxml2::XMLElement *root = doc.RootElement();
    if (root == nullptr)
    {
        std::cout << "Failed to open XML file" << std::endl;
        return 0;
    }

    // Считываем устройство
    tinyxml2::XMLElement *deviceElement = root->FirstChildElement("device");
    if (deviceElement == nullptr)
    {
        std::cout << "Failed to find device element" << std::endl;
        return 0;
    }

    while (deviceElement != nullptr)
    {
        tinyxml2::XMLAttribute const *attr_id = deviceElement->FindAttribute("id");
        tinyxml2::XMLAttribute const *attr_protocol = deviceElement->FindAttribute("protocol");
        tinyxml2::XMLAttribute const *attr_title = deviceElement->FindAttribute("title");

        if (attr_id != nullptr)
        {
            std::uint8_t device_id = std::stoul(attr_id->Value());
            modbus_unit *unit = new modbus_unit(device_id, attr_protocol->Value(), attr_title->Value());

            tinyxml2::XMLElement *registerElement = deviceElement->FirstChildElement("register");

            while (registerElement != nullptr)
            {
                tinyxml2::XMLAttribute const *attr_address = registerElement->FindAttribute("address");
                tinyxml2::XMLAttribute const *attr_value = registerElement->FindAttribute("value");
                tinyxml2::XMLAttribute const *attr_dataType = registerElement->FindAttribute("dataType");
                tinyxml2::XMLAttribute const *attr_regType = registerElement->FindAttribute("regType");

                std::uint16_t reg_address = std::stoul(attr_address->Value(), nullptr, 16);
                unit->add_register(reg_address, attr_value->Value(), attr_dataType->Value(), attr_regType->Value());

                registerElement = registerElement->NextSiblingElement("register");
            }
            units.push_back(unit);
        }
        deviceElement = deviceElement->NextSiblingElement("device");
    }

    struct event_base *base = event_base_new();

    server server(base);

    server.start();
    
    for (const auto &unit : units) {
        unit->display_info();
    }

    event_base_dispatch(base);
    event_base_free(base);

    return 0;
}
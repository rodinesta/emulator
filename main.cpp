#include <iostream>
#include <filesystem>
#include "tinyxml2.h"

int main()
{
    tinyxml2::XMLDocument doc;

    std::filesystem::path currentPath = std::filesystem::current_path().parent_path();

    // Определяем относительный путь к файлу конфигурации
    std::string confFilePath = currentPath.string() + "/conf.xml";

    std::cout << confFilePath << std::endl;

    // Загружаем файл
    doc.LoadFile(confFilePath.c_str());

    // Проверяем файл на целостность
    tinyxml2::XMLElement *root = doc.RootElement();
    if (root == nullptr)
    {
        std::cout << "Failed to open XML file" << std::endl;
        return 1;
    }

    // Считываем устройство
    tinyxml2::XMLElement *deviceElement = root->FirstChildElement("device");
    if (deviceElement == nullptr)
    {
        std::cout << "Failed to find device element" << std::endl;
        return 1;
    }

    std::string deviceId = deviceElement->Attribute("id");
    std::string protocol = deviceElement->Attribute("protocol");
    std::string deviceTitle = deviceElement->Attribute("title");

    std::cout << "Device ID: " << deviceId << std::endl;
    std::cout << "Protocol: " << protocol << std::endl;
    std::cout << "Title: " << deviceTitle << std::endl;

    tinyxml2::XMLElement *coilElement = deviceElement->FirstChildElement("Coil");

    while (coilElement != nullptr)
    {
        std::string coilAddress = coilElement->FirstChildElement("address")->GetText();
        std::string coilDescription = coilElement->FirstChildElement("description")->GetText();
        std::string coilValue = coilElement->FirstChildElement("value")->GetText();

        std::cout << "Coil address: " << coilAddress << std::endl;
        std::cout << "Coil description: " << coilDescription << std::endl;
        std::cout << "Coil value: " << coilValue << std::endl;

        coilElement = coilElement->NextSiblingElement("Coil");
    }

    return 0;
}
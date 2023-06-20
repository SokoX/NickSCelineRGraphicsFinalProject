#include "DiamondSquare.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

DiamondSquare::DiamondSquare(){

};

void saveHelper(std::string modeName, std::string terrainName, std::vector<uint8_t> pixelData, uint8_t max)
{
    std::ofstream outFile;
    outFile.open(terrainName + "_" + modeName + ".ppm");
    int component_count = 0;
    outFile << "P3" << std::endl;
    outFile << std::to_string(513) + " " + std::to_string(513) << std::endl;
    outFile << max << std::endl;
    int size = pixelData.size();
    while (component_count < size)
    {
        outFile << std::to_string(pixelData[component_count]) << std::endl;
        component_count++;
    }
    outFile.close();
}

void DiamondSquare::save(bool mode)
{
    // save height map
    if (mode == true)
    {
        saveHelper("height_map", terrainName, pixelData, max);
    }
    else
    { // save color map
        saveHelper("color_map", terrainName, pixelData, max);
    }
};

DiamondSquare::~DiamondSquare(){

};

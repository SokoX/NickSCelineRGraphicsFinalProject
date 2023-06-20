#ifndef DIAMONDSQUARE_HPP
#define DIAMONDSQUARE_HPP

#include <vector>
#include <string>

struct DiamondSquare
{

    // Fields
    std::vector<uint8_t> pixelData;
    std::vector<uint8_t> colorData;
    uint8_t max;
    uint8_t waterLevel;

    // Methods

    // Generates a random terrain heightmap
    void genRandom();
    // Generates the corresponding color map
    void genColorMap();
    // Creates and saves a ppm for the height or color map
    void save(bool mode);
    // Does the 'Square' Step of the algorithm
    void Square();
    // Does the 'Diamond' step of the algorithm
    void Diamond();
};

#endif

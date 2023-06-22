#ifndef DIAMONDSQUARE_HPP
#define DIAMONDSQUARE_HPP

#include <vector>
#include <string>

struct DiamondSquare
{

    // Fields
    std::vector<uint8_t> pixelData;
    std::vector<uint8_t> colorData;
    unsigned int max;
    unsigned int waterLevel;
    std::string terrainName;
    unsigned int size;

    // Empty Constructor
    DiamondSquare();

    // Constructor
    DiamondSquare(std::string name, unsigned int water);

    // Destructor
    ~DiamondSquare();

    // Methods

    // Generates a random terrain heightmap
    void genRandom();
    // Generates the corresponding color map
    void genColorMap();
    // Creates and saves a ppm for the height or color map
    void save(bool mode);
    // Does the 'Square' Step of the algorithm
    // void Square(uint8_t middle, uint8_t step);
    // Does the 'Diamond' step of the algorithm
    // void Diamond(uint8_t middle, uint8_t step);
};

#endif

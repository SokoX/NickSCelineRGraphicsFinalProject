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
    int currMode;
    int currVar;

    // Empty Constructor
    DiamondSquare();

    // Constructor
    DiamondSquare(std::string name, unsigned int water);

    // Destructor
    ~DiamondSquare();

    // Methods

    // Generates a random terrain heightmap
    void genRandom(int r);
    // Generates the corresponding color map
    void genColorMap(int mode);
    // Creates and saves a ppm for the height or color map
    void save(bool mode);

    // RELICS, supposed to be helpers but did anything but help :DDD
    //
    // Does the 'Square' Step of the algorithm
    // void Square(uint8_t middle, uint8_t step);
    // Does the 'Diamond' step of the algorithm
    // void Diamond(uint8_t middle, uint8_t step);
    
    // Clears pixelData and colorData
    void clearData();
};

#endif

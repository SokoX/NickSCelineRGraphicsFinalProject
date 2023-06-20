#ifndef DIAMONDSQUARE_HPP
#define DIAMONDSQUARE_HPP

#include <vector>
#include <string>

struct DiamondSquare{

    // Fields
    vector<uint_8> pixelData;
    vector<uint_8> colorData;
    uint_8 max;
    uint_8 waterLevel;

    // Constructor
    DiamondSquare();

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
    void Square();
    // Does the 'Diamond' step of the algorithm
    void DIamond();

};

#endif

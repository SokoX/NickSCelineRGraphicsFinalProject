#include "DiamondSquare.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>

// Empty Constructor
DiamondSquare::DiamondSquare(){
	
	srand(time(0));
}

// Constructor
DiamondSquare::DiamondSquare(std::string name, unsigned int water)
{

    terrainName = name;
    max = 255;
    size = 513; 
    waterLevel = water;
    currMode = 0;
    currVar = 128;

    std::cout << "built! with size " << size << std::endl;

    srand(time(0));
};

// Destructor
DiamondSquare::~DiamondSquare(){

};

void saveHelper(std::string modeName, std::string terrainName, std::vector<uint8_t> pixelData, unsigned int m, unsigned int waterLevel)
{
    std::string filePath = terrainName + "_" + modeName + ".ppm";

    // Trying to remove files of the same name. UNSUCCESSFUL FIRST TRY
    // int len = filePath.length();
    // char fileName[len] = filePath.c_str();

    char *fileName = &filePath[0];

    std::ifstream inFile;

    inFile.open(filePath);

    if(inFile.is_open()){
	remove(fileName);
    }

    std::ofstream outFile;
    outFile.open(filePath);
    int component_count = 0;
    outFile << "P3" << std::endl;
    outFile << std::to_string(513) + " " + std::to_string(513) << std::endl;
    outFile << m << std::endl;
    int size = pixelData.size();
    while (component_count < size)
    {
        if (modeName == "height_map" && pixelData[component_count] < waterLevel)
        {
            outFile << waterLevel << std::endl;
        }
        else
        {
            outFile << std::to_string(pixelData[component_count]) << std::endl;
        }

        component_count++;
    }
    outFile.close();
}

void DiamondSquare::save(bool mode)
{

    // save height map
    if (mode == true)
    {
        saveHelper("height_map", terrainName, pixelData, max, waterLevel);
    }
    else
    { // save color map
        saveHelper("color_map", terrainName, colorData, max, waterLevel);
    }
};

void DiamondSquare::genColorMap(int mode)
{
   
	currMode = mode;

    // Two other variations which failed miserably...
    //
    // for (int i = 0; i < pixelData.size(); i = i + 3)
    // {
    //     uint8_t x = pixelData[i];
    //     if (x <= waterLevel)
    //     {
    //         colorData.push_back(0);
    //         colorData.push_back(255);
    //         colorData.push_back(255);
    //     }
    //     else
    //     {
    //         colorData.push_back(x);
    //         colorData.push_back(255);
    //         colorData.push_back(x);
    //     }
    // }

    // for (int i = 0; i < size * 3; i++)
    // {
    //     for (int j = 0; j < size; j++)
    //     {

    //         uint8_t x = pixelData[i + (j * (size * 3))];
    //         if (x <= waterLevel)
    //         {
    //             colorData.push_back(0);
    //             colorData.push_back(255);
    //             colorData.push_back(255);
    //         }
    //         else
    //         {
    //             colorData.push_back(x);
    //             colorData.push_back(255);
    //             colorData.push_back(x);
    //         }
    //     }
    // }

    if(mode == 2){
        for (int i = (size * 3) - 3; i >= 0; i -= 3)
    	{
            for (int j = size - 1; j >= 0; j--)
            {
            	uint8_t x = pixelData[i + (j * (size * 3))];
            	if (x <= waterLevel)
            	{
                    colorData.push_back(255);
                    colorData.push_back(150);
                    colorData.push_back(40);
		}
            	else
            	{
                    int sum = x - (waterLevel - 70);
                    colorData.push_back(std::min(255, sum));
                    colorData.push_back(90);
                    colorData.push_back(90);
                }
            }
        }
    }

    

    else{
        for (int i = (size * 3) - 3; i >= 0; i -= 3)
    	{
            for (int j = size - 1; j >= 0; j--)
            {
            	uint8_t x = pixelData[i + (j * (size * 3))];
            	if (x <= waterLevel)
            	{
                    colorData.push_back(0);
                    colorData.push_back(255);
                    colorData.push_back(255);
		}
            	else
            	{
                    int sum = x - (waterLevel / 2);
                    colorData.push_back(sum);
                    colorData.push_back(255);
                    colorData.push_back(sum);
                }
            }
        }
    }
}

// helper to genRandom()

int random(uint8_t val)
{

    return ((rand() % ((2 * val) + 1)) - val);
}
// Generates the Random Terrain heightmap
void DiamondSquare::genRandom(int r)
{

    currVar = r;

    int arr[513][513];

    arr[0][0] = rand() % 256;
    arr[0][512] = rand() % 256;
    arr[512][0] = rand() % 256;
    arr[512][512] = rand() % 256;
    int step = size - 1;
    int rand_val = r;

    std::cout << arr[0][0] << std::endl;
    std::cout << arr[0][512] << std::endl;
    std::cout << arr[512][0] << std::endl;
    std::cout << arr[512][512] << std::endl;

    while (step > 1)
    {
        int half = step / 2;

        // Completing the Square Step
        for (int a = 0; a < (size - 1); a += step)
        {
            for (int b = 0; b < (size - 1); b = b + step)
            {

                arr[a + half][b + half] =
                    ((arr[a][b] +
                      arr[a][b + step] +
                      arr[a + step][b] +
                      arr[a + step][b + step]) /
                     4) +
                    random(rand_val);

                if (arr[a + half][b + half] > max)
                {

                    arr[a + half][b + half] = max;
                }

                if (arr[a + half][b + half] < 0)
                {

                    arr[a + half][b + half] = 0;
                }
            }
        }

        // Completing the Diamond Step
        for (int c = 0; c < size; c += half)
        {
            for (int d = (c + half) % step; d < size; d += step)
            {
                int num = 0;
                int value = 0;
                if ((c - half) >= 0)
                {
                    value += arr[c - half][d];
                    num++;
                }
                if ((d - half) >= 0)
                {
                    value += arr[c][d - half];
                    num++;
                }
                if ((d + half) < size)
                {
                    value += arr[c][d + half];
                    num++;
                }
                if ((c + half) < size)
                {
                    value += arr[c + half][d];
                    num++;
                }

                arr[c][d] = (value / num) + random(rand_val);

                if (arr[c][d] > max)
                {

                    arr[c][d] = max;
                }

                if (arr[c][d] < 0)
                {

                    arr[c][d] = 0;
                }
            }
        }

        step /= 2;
        rand_val /= 2;
    }

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            int temp = arr[x][y];
            pixelData.push_back(temp);
            pixelData.push_back(temp);
            pixelData.push_back(temp);
        }
    }
}


// I AM ANGRY AT THESE METHODS >:(
//
// Does NOT DO the Square Step
// void Square(uint8_t middle, uint8_t step){
//
//	for(int a = 0; a < size; a += step){
//		for(int b = 0; b < size; b += step){
//
//
//		}
//	}
//
//}

// Does NOT DO the Diamond Step
// void Diamond(uint8_t middle, uint8_t step){
//
//}

void DiamondSquare::clearData(){
	pixelData.clear();
	colorData.clear();
}

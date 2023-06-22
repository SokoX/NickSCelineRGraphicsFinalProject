// Support Code written by Michael D. Shah
// Last Updated: 6/11/21
// Please do not redistribute without asking permission.

// Functionality that we created
#include "SDLGraphicsProgram.hpp"

#include <string>
#include <iostream>


int main(int argc, char** argv){
	
	// Inital attempt. Moved into SDLGraphicsProgram.cpp ~~~
	//
	//	DiamondSquare heightmap("test", 9);
	//	heightmap.genRandom();
	//	heightmap.genColorMap();
	//	heightmap.save(true);
	//	heightmap.save(false);

	if(argc == 2){

		std::string str = argv[1];

		SDLGraphicsProgram mySDLGraphicsProgram(1280, 720, str, 100);

		// Run Our Program forever!
		mySDLGraphicsProgram.Loop();

	}
	// Create an instance of an object for a SDLGraphicsProgram
	else if(argc == 3){

		std::string str = argv[1];

		std::string num = argv[2];

		unsigned int w = stoul(num, nullptr, 0);

		SDLGraphicsProgram mySDLGraphicsProgram(1280, 720, str, w);

		// Run Our Program forever!
		mySDLGraphicsProgram.Loop();

	}
	else{
		std::cerr << "You must provide either 1 or 2 arguments!";
		std::cerr << "Acceptable inputs are:";
		std::cerr << "lab.exe given_name";
		std::cerr << "lab.exe given_name water_level";

	}

	return 0;
}

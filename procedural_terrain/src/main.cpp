// Support Code written by Michael D. Shah
// Last Updated: 6/11/21
// Please do not redistribute without asking permission.

// Functionality that we created
#include "SDLGraphicsProgram.hpp"
#include "DiamondSquare.hpp"

int main(int argc, char** argv){
	
	DiamondSquare heightmap("test", 9);
	heightmap.genRandom();
	heightmap.genColorMap();
	heightmap.save(true);
	heightmap.save(false);
	// Create an instance of an object for a SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(1280,720);
	// 1280, 720
	// Run our program forever
	mySDLGraphicsProgram.Loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}

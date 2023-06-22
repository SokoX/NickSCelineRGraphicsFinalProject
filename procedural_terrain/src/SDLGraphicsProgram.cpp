#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "DiamondSquare.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h, std::string name, unsigned int water)
{
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    m_window = NULL;

    // Setting given terrain name and  water level
    terr_name = name;
    waterLevel = water;

    CurrentMaps.terrainName = terr_name;
    CurrentMaps.waterLevel = waterLevel;
    CurrentMaps.max = 255;
    CurrentMaps.size = 513;


    CurrentMaps.genRandom();
    CurrentMaps.genColorMap();
    CurrentMaps.save(true);
    CurrentMaps.save(false);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else
    {
        // Use OpenGL 3.3 core
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        // We want to request a double buffer for smooth updating.
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
     

        // Create window
        m_window = SDL_CreateWindow("Lab",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    w,
                                    h,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        // Check if Window did not create.
        if (m_window == NULL)
        {
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Create an OpenGL Graphics Context
        m_openGLContext = SDL_GL_CreateContext(m_window);
        if (m_openGLContext == NULL)
        {
            errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Initialize GLAD Library
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        {
            errorStream << "Failed to iniitalize GLAD\n";
            success = false;
        }

        // Initialize OpenGL
        if (!InitGL())
        {
            errorStream << "Unable to initialize OpenGL!\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if (!success)
    {
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors = errorStream.str();
        SDL_Log("%s\n", errors.c_str());
    }
    else
    {
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

    // SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
    GetOpenGLVersionInfo();

    // Setup our Renderer
    m_renderer = new Renderer(w, h);
}

// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram()
{
    if (m_renderer != nullptr)
    {
        delete m_renderer;
    }

    // Destroy window
    SDL_DestroyWindow(m_window);
    // Point m_window to NULL to ensure it points to nothing.
    m_window = nullptr;
    // Quit SDL subsystems
    SDL_Quit();
}

// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL()
{
    // Success flag
    bool success = true;

    return success;
}

// Loops forever!
void SDLGraphicsProgram::Loop()
{

    // Create our terrain
    std::string temp1 = CurrentMaps.terrainName + "_height_map.ppm";
    Terrain *myTerrain = new Terrain(513, 513, temp1);

    std::string temp2 = CurrentMaps.terrainName + "_color_map.ppm";
    myTerrain->LoadTexture(temp2);

    // Create a node for our terrain
    SceneNode *terrainNode;
    terrainNode = new SceneNode(myTerrain);
    // Set our SceneTree up
    m_renderer->setRoot(terrainNode);

    // Set a default position for our camera
    m_renderer->GetCamera(0)->SetCameraEyePosition(125.0f, 50.0f, 500.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 5.0f;

    // While application is running
    while (!quit)
    {

        // For our terrain setup the identity transform each frame
        // TODO maybe move this XXXXX NO 
        terrainNode->GetLocalTransform().LoadIdentity();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
	{
        
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
	    if (e.type == SDL_KEYDOWN){

		if (e.key.keysym.sym == SDLK_r){
			
			CurrentMaps.clearData();
			CurrentMaps.genRandom();
    			CurrentMaps.genColorMap();
   	 		CurrentMaps.save(true);
   			CurrentMaps.save(false);

			myTerrain->Reset(temp1);
			myTerrain->LoadTexture(temp2);
		}
	    }


            // Handle keyboard input for the camera class
            //             if(e.type==SDL_MOUSEMOTION){
            //                 // Handle mouse movements
            //                 int mouseX = e.motion.x;
            //                 int mouseY = e.motion.y;
            // //              m_renderer->camera->mouseLook(mouseX, mouseY);
            //             }
            // switch(e.type){
            //     // Handle keyboard presses
            //     case SDL_KEYDOWN:
            //         switch(e.key.keysym.sym){
            //             case SDLK_LEFT:
            //                 m_renderer->GetCamera(0)->MoveLeft(cameraSpeed);
            //                 break;
            //             case SDLK_RIGHT:
            //                 m_renderer->GetCamera(0)->MoveRight(cameraSpeed);
            //                 break;
            //             case SDLK_UP:
            //                 m_renderer->GetCamera(0)->MoveForward(cameraSpeed);
            //                 break;
            //             case SDLK_DOWN:
            //                 m_renderer->GetCamera(0)->MoveBackward(cameraSpeed);
            //                 break;
            //             case SDLK_RSHIFT:
            //                 m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
            //                 break;
            //             case SDLK_RCTRL:
            //                 m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
            //                 break;
            //         }
            //     break;
            // }
        } // End SDL_PollEvent loop.

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W])
        {
            // gCamera.MoveForward(0.05f);
            m_renderer->GetCamera(0)->MoveForward(cameraSpeed);
        }
        if (state[SDL_SCANCODE_S])
        {
            // gCamera.MoveBackward(0.05f);
            m_renderer->GetCamera(0)->MoveBackward(cameraSpeed);
        }
        if (state[SDL_SCANCODE_A])
        {
            // gCamera.MoveLeft(0.05f);
            m_renderer->GetCamera(0)->MoveLeft(cameraSpeed);
        }
        if (state[SDL_SCANCODE_D])
        {
            // gCamera.MoveRight(0.05f);
            m_renderer->GetCamera(0)->MoveRight(cameraSpeed);
        }
        if (state[SDL_SCANCODE_UP])
        {

            m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            
            m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
        }
	if (state[SDL_SCANCODE_Q])
	{
		
	    quit = true;
	}


        int mouseX, mouseY;
        SDL_GetGlobalMouseState(&mouseX, &mouseY);
        // gCamera.MouseLook(mouseX, mouseY);
        m_renderer->GetCamera(0)->MouseLook(mouseX, mouseY);

        // Update our scene through our renderer
        m_renderer->Update();
        // Render our scene using our selected renderer
        m_renderer->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25); // TODO: You can change this or implement a frame
                       // independent movement method if you like.
        // Update screen of our specified window
        SDL_GL_SwapWindow(GetSDLWindow());
    }
    // Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window *SDLGraphicsProgram::GetSDLWindow()
{
    return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo()
{
    SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
    SDL_Log("Vendor: %s", (const char *)glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s", (const char *)glGetString(GL_RENDERER));
    SDL_Log("Version: %s", (const char *)glGetString(GL_VERSION));
    SDL_Log("Shading language: %s", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

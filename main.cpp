#include <iostream>
#include <thread>
#include <chrono>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "helpers.h"
#include "character.h"
#include "world.h"

using namespace std;

int main()
{
    // SpriteSheet Filename
    string spriteFilename = SPRITEFILENAME; // Leave this line

    // Setup and Load Texture object here
    Texture myTexture;
    myTexture.loadFile(spriteFilename, 20, 20);
    Tile::tileWidth = 20;
    Tile::tileHeight = 20;

    World myWorld(MAZEFILENAME, myTexture.tileWidth(),
                  myTexture.tileHeight());
	myTexture.scaleGraphics(myWorld.rows, myWorld.cols);

    bool quit = false;
    //Character myPacman(0,0,Pacman);
    int frame = 0;
    while(!quit){
        // Handle any SDL Events
        // Such as resize, clicking the close button,
        //  and process and key press events.
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            //myPacman.handle_event(e);
            myWorld.pacman.handle_event(e);
        }

        // Update the Game State Information
        myWorld.UpdateWorld();

        // Draw the current state to the screen.
        SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(myTexture.myWin.sdlRenderer);

        //myPacman.render(&myTexture, frame);
        myWorld.render(&myTexture, frame);
        SDL_RenderPresent(myTexture.myWin.sdlRenderer);
	
	++frame;
	
        this_thread::sleep_for(chrono::milliseconds(75));
    }

    return 0;
}

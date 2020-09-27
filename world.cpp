#include "world.h"
#include "helpers.h"
#include "character.h"
#include "DFS.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
/**
 * Constructs the World object loading a maze from the supplied file.
 * It should initialise the \ref{map} array with the relevant tiles as well
 * as the pacman and ghost objects.
 *
 * @param filename - File from which the maze should be read.
 * @param tileWidth - Width of each tile
 * @param tileHeight - Height of each tile
 */
World::World(string filename, int tileWidth, int tileHeight)
    : food(0), points(0), ready(true), Dead(false), Scared(false), Killed(false), pacman(0,0,Pacman), pacmand(0,0,PacmanD), ghostR(0,0,GhostR), ghostD(0,0,GhostD),
      game_over(makeTile(0,0,GameOver))//, ghostE(0,0,GhostE)
{
    ifstream f(filename);
    if(!f.is_open())
        throw runtime_error("Couldn't open maze file " + filename);

    f >> rows >> cols;
    string curr;
    getline(f, curr);

    for(int r = 0; r < rows; ++r){
        getline(f, curr);
        vector<Tile> row;
        for(int c = 0; c < cols; ++c){
            int x = c*tileWidth;
            int y = r*tileHeight;
            switch(curr[c]){
            case 'x':
                row.push_back(makeTile(x,y,Wall));
                break;
            case ' ':
                row.push_back(makeTile(x,y,Blank));
                break;	
            case '.':
                food++;
                row.push_back(makeTile(x,y,Food));
                break;
	case 'c': 
		food++;
		row.push_back(makeTile(x,y,Cherry));
		break;
            case '0':
                pacman.x = x;
                pacman.y = y;
                row.push_back(makeTile(x,y,Blank));
                break;
	case 'z': 		
		row.push_back(makeTile(x,y,PacmanD));
		break;
            case '1':
		ghostR.x=x;
		ghostR.y=y;
                row.push_back(makeTile(x,y,Blank));
                break;
            case '2':
                row.push_back(makeTile(x,y,GhostP));
                break;
            case '3':
                row.push_back(makeTile(x,y,GhostB));
                break;
            case '4':
                row.push_back(makeTile(x,y,GhostY));
                break;
	case 'd': 
		row.push_back(makeTile(x,y,GhostD));
		break;
	case 'e': 
		row.push_back(makeTile(x,y,GhostE));
		break;
            }
        }
        maze.push_back(row);
	
    }
    game_over.x = (cols-5)*tileWidth/2;
    game_over.y = (rows)*tileHeight/2;
}

/**
 * Renders the World to the ::sdlRenderer buffer.
 * It calls the respective render functions on each tile first.
 * Following this, it calls the pacman and ghost objects to render
 * them above the background.
 * @param frame [optional] An optional frame number to pass to the objects to handle animation.
 */
void World::render(Texture *t, int frame)
{
	for(int r = 0;r < rows; ++r){
		for(int c = 0; c < cols; ++c){
		Tile &curr = maze[r][c];
            	curr.render(t, frame);
		if(unvisited[r][c] == 1){
			SDL_Rect r{curr.x+2, curr.y+2, 18,18};
			SDL_SetRenderDrawColor(t->myWin.sdlRenderer, 255, 255, 255,255);

			SDL_RenderDrawRect(t->myWin.sdlRenderer, &r);
		}
        }
    }

	if ((Scared==false))
		{
		ghostR.render(t,frame);
		}
	else
		{
		ghostD.x=ghostR.x;
		ghostD.y=ghostR.y;
		//ghostE.x=ghostR.x;
		//ghostE.y=ghostR.y;
		
			if ((Killed==false))
				{
				ghostD.render(t, frame);
				}
			/*else
				{
				ghostD.render(t,frame);
				}*/
		}


if ((Dead==false)){
pacman.render(t, frame);
if(points == food)
        game_over.render(t, frame/10);
}
else{
pacmand.x=pacman.x;
pacmand.y=pacman.y;
pacmand.render(t, frame/3);
game_over.render(t, frame/10);
}
}

/**
 * This function is responsible for advancing the game state.
 * Pacman and the ghosts should be moved (if possible). If pacman is
 * captured by a ghost pacman.dead should be set to true. If pacman eats
 * a food pellet the relevant totals should be updated.
 *
 * @return The same value as World::ready, indicating whether the game is finished.
 */
bool World::UpdateWorld()
{
    SDL_Rect next_pos = pacman.getNextPosition();


    bool move_pacman = true;
    // loop over all wall tiles and check for coll.
    for(int r = 0; r < rows && move_pacman; ++r){
        for(int c = 0; c < cols && move_pacman; ++c){
            if(maze[r][c].myType == Wall){
                SDL_Rect w = {maze[r][c].x,
                              maze[r][c].y,
                              Tile::tileWidth*maze[r][c].w,
                              Tile::tileHeight*maze[r][c].h};
                if(collision(next_pos, w, 3, 2)){
                    move_pacman = false;
                }
            }
if ((Scared==false)){
	if(maze[r][c].x==ghostR.x && maze[r][c].y==ghostR.y){
                SDL_Rect w = {ghostR.x,
                              ghostR.y,
                              Tile::tileWidth*maze[r][c].w,
                              Tile::tileHeight*maze[r][c].h};
                if(collision(next_pos, w, 3, 2)){
                    move_pacman = false;
			Dead=true;
        }
    }
	
}
else
{
if(maze[r][c].x==ghostD.x && maze[r][c].y==ghostD.y){
                SDL_Rect w = {ghostD.x,
                              ghostD.y,
                              Tile::tileWidth*maze[r][c].w,
                              Tile::tileHeight*maze[r][c].h};
                if(collision(next_pos, w, 3, 2)){
                    move_pacman = true;
		 Killed = true;
		maze[r][c] = makeTile(w.x, w.y, GhostE);
}
}
}
}
}
    if(Dead==false && move_pacman && food != points){
        pacman.x = next_pos.x;
        pacman.y = next_pos.y;

        for(int r = 0; r < rows; ++r){
            for(int c = 0; c < cols; ++c){
                if(maze[r][c].myType == Food){
                    SDL_Rect w = {maze[r][c].x,
                                  maze[r][c].y,
                                  Tile::tileWidth*maze[r][c].w,
                                  Tile::tileHeight*maze[r][c].h};
                    if(collision(next_pos, w, 3, 5)){
                        maze[r][c] = makeTile(w.x, w.y, Blank);
                        points++;
                    }
                }
			if(maze[r][c].myType == Cherry){     
                            SDL_Rect w={maze[r][c].x,
                                        maze[r][c].y,
                                        Tile::tileWidth*maze[r][c].w,
                                  	Tile::tileHeight*maze[r][c].h};
                            if(collision(next_pos, w, 3, 5)){
				Scared=true;
                                maze[r][c]=makeTile(w.x,w.y,Blank);
                                points++;				
				}
                           	}
            }
 	}

    }

    //return (food == points);

    DFS w(maze, pacman, ghostR);
        w.unvisit();
        w.search(w.start);

        //SDL_Rect ghostmove = ghostR.ghostNextPosition();

	
    if(w.path==false){
	cout << "No Path" << endl;
                unvisited = w.unvisited;
            while(!w.parent.empty() && w.path!=true){
                pair<int,int>branch = w.backtrack();
		cout<<"Backtrack"<<endl;
                w.search(branch);
        }
    }//else{
    //cout << w.parent.size()<<endl ;
    if(w.path ==true){
	cout<<"Path Found"<<endl;
        unvisited = w.unvisited;
        moves = w.getParent() ;
        cout<<"Parent Size:"<<moves.size()<<endl;
        pair<int,int>temp = w.moving();
        cout<<"Temp Coordinates:("<<temp.first<<","<<temp.second<<")"<<endl;
        ghostR.x = temp.second*20 ;
        ghostR.y = temp.first*20 ;
        cout<<"Ghost Coordinates:("<<ghostR.x<<","<<ghostR.y<<")"<<endl;
        //w.parent.clear();
          }
    return 0;

//			DFS w(FILENAME);
//				w.unvisit();
//				w.DFS(w.start);
//
//				if(w.path == false){
//
//				    while(!w.parent.empty() && w.path != true){
//
//					pair<int,int>branch = w.backtrack();
//					w.DFS(branch);
//				    }
//				}
//				if(w.path == true){
//				move=w.parent.front();
//				ghostR.x=move.first*20;
//				ghostR.y=move.second*20;
//					}
//			return 0;
}


















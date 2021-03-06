#include "helpers.h"
#include "tile.h"

using namespace std;

/**
 * @brief makeTile Creates a Tile based on the TileType
 *
 * Remember that the different TileTypes are:
 *      Wall        {{7,16}}
 *      Food        {{10,1}}
 *      Blank       {{1,4}}
 *      Pacman
 *          Up      {{3,1},{3,2},{3,1},{3,3}}
 *          Down    {{4,1},{4,2},{4,1},{4,3}}
 *          Left    {{1,1},{1,2},{1,1},{1,3}}
 *          Right   {{2,1},{2,2},{2,1},{2,3}}
 *      MrsPacman
 *          Up      {{3,5},{3,6},{3,5},{3,7}}
 *          Down    {{4,5},{4,6},{4,5},{4,7}}
 *          Left    {{1,5},{1,6},{1,5},{1,7}}
 *          Right   {{2,5},{2,6},{2,5},{2,7}}
 *      GhostR
 *          Up      {{5,1},{5,2}}
 *          Down    {{5,3},{5,4}}
 *          Left    {{5,5},{5,6}}
 *          Right   {{5,7},{5,8}}
 *      GhostP, GhostY, GhostB
 *
 * @param x X Window co-ordinate in pixels.
 * @param y Y Window co-ordinate in pixels.
 * @param t Type of the Tile to construct.
 * @param dir Direction of the Tile (Up/Down/Left/Right)
 * @return The new Tile created using the parameters.
 */
Tile makeTile(int x, int y, TileType t, Direction dir)
{
    switch(t){
	case GhostD:
	return Tile(x, y, {{9,1},{9,4},{9,2},{9,3}},t,1,1);
	case GhostE:
	return Tile(x, y, {{11,1},{11,3},{11,2},{11,4}},t,1,1);
    case GameOver:
        return Tile(x, y, {{8,12}, {7,11}},t,5,1);
	case PacmanD:
	return Tile(x, y, {{13,1},{13,2},{13,3},{13,4},{13,5},{13,6},{13,7},{13,8},{13,9},{13,10},{13,11}},t,1,1);
    case Wall:
        return Tile(x, y, {{7,16}},t,1,1);
    case Food:
        return Tile(x, y, {{10,1}},t,1,1);
    case Blank:
        return Tile(x, y, {{1,4}},t,1,1);
	case Cherry:
			return Tile(x, y, {{9,14}},t,1,1);
    case Pacman:
        switch(dir){
        case Up:
            return Tile(x, y, {{3,1},{3,2},{3,1},{3,3}},t,1,1);
        case Left:
            return Tile(x, y, {{1,1},{1,2},{1,1},{1,3}},t,1,1);
        case Down:
            return Tile(x, y, {{4,1},{4,2},{4,1},{4,3}},t,1,1);
        case Right:
        default:
            return Tile(x, y, {{2,1},{2,2},{2,1},{2,3}},t,1,1);
        }
    case MrsPacman:
        switch(dir){
        case Up:
            return Tile(x, y, {{3,4+1},{3,4+2},{3,4+1},{3,4+3}},t,1,1);
        case Left:
            return Tile(x, y, {{1,4+1},{1,4+2},{1,4+1},{1,4+3}},t,1,1);
        case Down:
            return Tile(x, y, {{4,4+1},{4,4+2},{4,4+1},{4,4+3}},t,1,1);
        case Right:
        default:
            return Tile(x, y, {{2,4+1},{2,4+2},{2,4+1},{2,4+3}},t,1,1);
        }
    case GhostR:
        switch(dir){
        case Up:
            return Tile(x, y, {{5,1},{5,2}},t,1,1);
        case Left:
            return Tile(x, y, {{5,5},{5,6}},t,1,1);
        case Down:
            return Tile(x, y, {{5,3},{5,4}},t,1,1);
        case Right:
        default:
            return Tile(x, y, {{5,7},{5,8}},t,1,1);
        }
    case GhostP:
        switch(dir){
        case Up:
            return Tile(x, y, {{6,1},{6,2}},t,1,1);
        case Left:
            return Tile(x, y, {{6,5},{6,6}},t,1,1);
        case Down:
            return Tile(x, y, {{6,3},{6,4}},t,1,1);
        case Right:
        default:
            return Tile(x, y, {{6,7},{6,8}},t,1,1);
        }
    case GhostB:
        switch(dir){
        case Up:
            return Tile(x, y, {{7,1},{7,2}},t,1,1);
        case Left:
            return Tile(x, y, {{7,5},{7,6}},t,1,1);
        case Down:
            return Tile(x, y, {{7,3},{7,4}},t,1,1);
        case Right:
        default:
            return Tile(x, y, {{7,7},{7,8}},t,1,1);
        }
    case GhostY:
        switch(dir){
        case Up:
            return Tile(x, y, {{8,1},{8,2}},t,1,1);
        case Left:
            return Tile(x, y, {{8,5},{8,6}},t,1,1);
        case Down:
            return Tile(x, y, {{8,3},{8,4}},t,1,1);
        case Right:
        default:
            return Tile(x, y, {{8,7},{8,8}},t,1,1);
        }
    default:
        return Tile(x, y, {{13,11}, {13,12}},t,1,1);
    }
    //return Tile(x, y, numFrames, t, spriteRow, spriteCol, 1, 1);
}

bool collision(SDL_Rect a, SDL_Rect b, int a_off, int b_off)
{

    int bottomA = a.y + a.h - a_off;
    int topA = a.y + a_off;
    int leftA = a.x + a_off;
    int rightA = a.x + a.w - a_off;

    int bottomB = b.y + b.h - b_off;
    int topB = b.y + b_off;
    int leftB = b.x + b_off;
    int rightB = b.x + b.w - b_off;

    // If A finishs above B - No Collision
    if(bottomA <= topB)
        return false;

    // If A starts below B - No Collision
    if(topA >= bottomB)
        return false;

    // If the right of A is left of B - No Collision
    if(rightA <= leftB)
        return false;

    // If the left of A is right of B - No Collision
    if(leftA >= rightB)
        return false;

    // If we get here there must be an overlap - Collision
    return true;
}


vector<Tile> getTestTiles()
{
    vector<Tile> testTiles;
    testTiles.push_back(makeTile(0 ,0,Pacman, Up));
    testTiles.push_back(makeTile(20,0,Pacman, Down));
    testTiles.push_back(makeTile(40,0,Pacman, Left));
    testTiles.push_back(makeTile(60,0,Pacman, Right));

    testTiles.push_back(makeTile(0 ,20,MrsPacman, Up));
    testTiles.push_back(makeTile(20,20,MrsPacman, Down));
    testTiles.push_back(makeTile(40,20,MrsPacman, Left));
    testTiles.push_back(makeTile(60,20,MrsPacman, Right));

    testTiles.push_back(makeTile(0 ,40,Wall));
    testTiles.push_back(makeTile(20,40,Blank));
    testTiles.push_back(makeTile(40,40,Food));

    int lastY = 40;
    for(TileType t : {GhostR, GhostY, GhostP, GhostB}){
        lastY += 20;
        testTiles.push_back(makeTile(0 ,lastY,t, Up));
        testTiles.push_back(makeTile(20,lastY,t, Down));
        testTiles.push_back(makeTile(40,lastY,t, Left));
        testTiles.push_back(makeTile(60,lastY,t, Right));
    }
    return testTiles;
}

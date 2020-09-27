#include "character.h"
#include "tile.h"
#include "helpers.h"

/**
 * @brief Character::Character
 * @param myX X window co-ordinate.
 * @param myY Y window co-ordinate.
 * @param t Type of character.
 */
Character::Character(int myX, int myY, TileType t)
    : x(myX), y(myY),
      uTile(makeTile(myX, myY, t, Up)),
      dTile(makeTile(myX, myY, t, Down)),
      lTile(makeTile(myX, myY, t, Left)),
      rTile(makeTile(myX, myY, t, Right))
{
    // The tiles above have to be constructed with the class above.
    // Why can't we rather just set their value in here using uTile = makeTile(...)?
}

/**
 * @brief Character::render Call the relevant tiles render function based on current direction.
 * @param t Texture object for rendering.
 * @param frame Frame number to render.
 */
void Character::render(Texture *t, int frame)
{
    switch (dir) {
    case Up:
        uTile.x = x;
        uTile.y = y;
        uTile.render(t, frame);
        break;
    case Down:
        dTile.x = x;
        dTile.y = y;
        dTile.render(t, frame);
        break;
    case Left:
        lTile.x = x;
        lTile.y = y;
        lTile.render(t, frame);
        break;
    case Right:
    default:
        rTile.x = x;
        rTile.y = y;
        rTile.render(t, frame);
        break;
    }
}
/**
 * @brief Character::getNextPosition Calculates the position of the character based on direction.
 * @return SDL_Rect of the position and dimensions (in pixels) of the character.
 */
SDL_Rect Character::getNextPosition()
{
    SDL_Rect newpos = {x, y, Tile::tileWidth*uTile.w, Tile::tileHeight*uTile.h};
    switch(dir){
    case Up:
        newpos.y -= 5;
        break;
    case Down:
        newpos.y += 5;
        break;
    case Left:
        newpos.x -= 5;
        break;
    case Right:
        newpos.x += 5;
        break;
    }

    return newpos; 
}

/*SDL_Rect Character::ghostNextPosition()
{
    SDL_Rect newpos = {x, y, Tile::tileWidth*uTile.w, Tile::tileHeight*uTile.h};
    switch(dir){
    case Up:
        newpos.y -= 5;
        break;
    case Down:
        newpos.y += 5;
        break;
    case Left:
        newpos.x -= 5;
        break;
    case Right:
        newpos.x += 5;
        break;
    }

    return newpos;
}*/

/**
 * @brief Character::handle_event Handles the SDL Events for Arrow Keypresses
 * @param e SDL_Event to check.
 */
void Character::handle_event(const SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:    dir = Up; break;
        case SDLK_DOWN:  dir = Down; break;
        case SDLK_LEFT:  dir = Left; break;
        case SDLK_RIGHT: dir = Right; break;
        }
    }
}

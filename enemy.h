#ifndef ENEMY_H
#define ENEMY_H

#include <QtGlobal>
#include "game.h"

struct Enemy
{
    int x,y,dx,dy;

      Enemy()
       {
        x=y=300;
        dx=4-rand()%8;
        dy=4-rand()%8;
       }

      void move()
       {
        x+=dx;
        if (Game::grid[y/Game::TILE_SIZE][x/Game::TILE_SIZE]==1)
        {
            dx=-dx;
            x+=dx;
        }
        y+=dy;
        if (Game::grid[y/Game::TILE_SIZE][x/Game::TILE_SIZE]==1)
        {
            dy=-dy;
            y+=dy;
        }
       }
};

#endif // ENEMY_H

#ifndef ENEMY_H
#define ENEMY_H

#include <QtGlobal>
#include "game.h"

struct Enemy
{
    int x,y,dx,dy, pixmapWidth, pixmapHeight;

      Enemy()
       {
        x=y=300;
        dx=4-rand()%8;
        dy=4-rand()%8;
        pixmapWidth = 40;
        pixmapHeight = 40;
       }

      void move()
       {
        x+=dx;
        if (Game::grid[y/Game::TILE_SIZE][x/Game::TILE_SIZE]==1)
        {
            dx=-dx;
            x+=dx;
        }
        if (Game::grid[y/Game::TILE_SIZE][(x+pixmapWidth/2)/Game::TILE_SIZE]==1)
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
        if (Game::grid[(y+pixmapHeight/2)/Game::TILE_SIZE][x/Game::TILE_SIZE]==1)
        {
            dy=-dy;
            y+=dy;
        }
       }
};

#endif // ENEMY_H

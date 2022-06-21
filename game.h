#ifndef GAME_H
#define GAME_H
#include <QSize>

class Game
{
public:
    Game();
    static void drop(int y,int x);
    static int grid[25][40];
    static int TILE_SIZE;
    static QSize RESOLUTION;
    static const QString PATH_TO_ENEMY_PIXMAP;
    static const QString PATH_TO_GAMEOVER_PIXMAP;
    static const QString PATH_TO_TILES_PIXMAP;
    static const QString PATH_TO_HERO_PIXMAP;
    static const QString PATH_TO_TILE_PIXMAP;
    static const QString PATH_TO_ACTIVE_TILE_PIXMAP;

    static const int N, M;
    static const float ITERATION_VALUE;
    static const float DELAY;
};

#endif // GAME_H

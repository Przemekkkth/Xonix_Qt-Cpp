#include "game.h"

int Game::grid[25][40] = {{0}};
int Game::TILE_SIZE = 18;
QSize Game::RESOLUTION = QSize(720, 450);// 40x18 25x18
const QString Game::PATH_TO_ENEMY_PIXMAP = ":/images/enemy.png";
const QString Game::PATH_TO_GAMEOVER_PIXMAP = ":/images/gameover.png";
const QString Game::PATH_TO_TILES_PIXMAP = ":/images/tiles.png";

const QString Game::PATH_TO_HERO_PIXMAP = ":/images/hero.png";
const QString Game::PATH_TO_TILE_PIXMAP = ":/images/tile.png";
const QString Game::PATH_TO_ACTIVE_TILE_PIXMAP = ":/images/active_tile.png";

const int Game::N = 40;
const int Game::M = 25;
const float Game::ITERATION_VALUE = 1000.0f/60.0f;
const float Game::DELAY = 70.0f;

Game::Game()
{

}

void Game::drop(int y, int x)
{
    if (grid[y][x]==0) grid[y][x]=-1;
    if (grid[y-1][x]==0) drop(y-1,x);
    if (grid[y+1][x]==0) drop(y+1,x);
    if (grid[y][x-1]==0) drop(y,x-1);
    if (grid[y][x+1]==0) drop(y,x+1);
}

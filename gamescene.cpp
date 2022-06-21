#include "gamescene.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_enemyCount(4), m_isGame(true), m_isReset(true), m_x(0), m_y(0), m_dx(0), m_dy(0), m_timer(0.0f)
    ,m_delay(0.07f), m_gameTimer(new QTimer(this)), m_moveUp(false), m_moveRight(false), m_moveDown(false), m_moveLeft(false), m_enemyRotation(0.0f)
{
    loadPixmaps();
    setSceneRect(0,0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    connect(m_gameTimer, &QTimer::timeout, this, &GameScene::update);
    m_gameTimer->start(Game::ITERATION_VALUE);

    for (int i = 0; i < Game::M; i++)
    {
        for (int j = 0; j < Game::N; j++)
        {
            if (i==0 || j==0 || i== Game::M-1 || j == Game::N-1)
            {
                Game::grid[i][j]=1;
            }
        }
    }

}

void GameScene::loadPixmaps()
{
    if(m_enemyPixmap.load(Game::PATH_TO_ENEMY_PIXMAP))
    {
        qDebug() << "EnemyPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "EnemyPixmap is not loaded successfully";
    }

    if(m_gameOverPixmap.load(Game::PATH_TO_GAMEOVER_PIXMAP))
    {
        qDebug() << "GameOverPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "GameOverPixmap is not loaded successfully";
    }

    if(m_heroPixmap.load(Game::PATH_TO_HERO_PIXMAP))
    {
        qDebug() << "HeroPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "HeroPixmap is not loaded successfully";
    }

    if(m_tilePixmap.load(Game::PATH_TO_TILE_PIXMAP))
    {
        qDebug() << "TilePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "TilePixmap is not loaded successfully";
    }

    if(m_activeTilePixmap.load(Game::PATH_TO_ACTIVE_TILE_PIXMAP))
    {
        qDebug() << "ActiveTilePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ActiveTilePixmap is not loaded successfully";
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    {
        m_moveUp = true;
    }
        break;
    case Qt::Key_Right:
    {
        m_moveRight = true;
    }
        break;
    case Qt::Key_Down:
    {
        m_moveDown = true;
    }
        break;
    case Qt::Key_Left:
    {
        m_moveLeft = true;
    }
        break;
    }
    if(!event->isAutoRepeat())
    {
        if(event->key() == Qt::Key_R)
        {
            m_isReset = true;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    {
        m_moveUp = false;
    }
        break;
    case Qt::Key_Right:
    {
        m_moveRight = false;
    }
        break;
    case Qt::Key_Down:
    {
        m_moveDown = false;
    }
        break;
    case Qt::Key_Left:
    {
        m_moveLeft = false;
    }
        break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::update()
{
    //update timer
    m_timer += Game::ITERATION_VALUE;
    qDebug() << m_timer << " " << Game::DELAY;
    //exit(0);
    //timer
    if(m_moveUp)
    {
        m_dx = 0;
        m_dy = -1;
    }
    if(m_moveRight)
    {
        m_dx = 1;
        m_dy = 0;
    }
    if(m_moveDown)
    {
        m_dx = 0;
        m_dy = 1;
    }
    if(m_moveLeft)
    {
        m_dx = -1;
        m_dy = 0;
    }


    if(m_isReset == true)
    {
        m_isReset = false;
        m_isGame = true;
        for (int i=1;i< Game::M-1;i++)
        {
            for (int j=1;j<Game::N-1;j++)
            {
                Game::grid[i][j]=0;
            }
        }

        m_x = 10;
        m_y = 0;
    }
    if( !m_isGame )
    {
        return;
    }



    if(m_timer > Game::DELAY)
    {
        m_timer = 0.0f;
        m_x += m_dx;
        m_y += m_dy;

        if (m_x < 0)
        {
            m_x = 0;
        }
        if (m_x > Game::N-1)
        {
            m_x = Game::N-1;
        }
        if (m_y < 0)
        {
            m_y = 0;
        }
        if ( m_y > Game::M-1)
        {
            m_y = Game::M-1;
        }

        if ( Game::grid[m_y][m_x] == 2)
        {
            m_isGame = false;
        }
        if (Game::grid[m_y][m_x] == 0)
        {
            Game::grid[m_y][m_x]=2;
        }

    }
    //end timer
    for (int i = 0; i < m_enemyCount; i++)
    {
        m_enemies[i].move();
    }

    if ( Game::grid[m_y][m_x] == 1)
    {
        m_dx = m_dy = 0;

        for (int i=0; i < m_enemyCount; i++)
        {
            Game::drop(m_enemies[i].y/Game::TILE_SIZE, m_enemies[i].x/Game::TILE_SIZE);
        }


        for (int i = 0; i < Game::M; i++)
        {
            for (int j = 0; j < Game::N; j++)
            {
                if ( Game::grid[i][j] == -1)
                {
                    Game::grid[i][j] = 0;
                }
                else
                {
                    Game::grid[i][j] = 1;
                }
            }

        }

    }

    for (int i=0; i < m_enemyCount; i++)
    {
        if  (Game::grid[m_enemies[i].y/Game::TILE_SIZE][m_enemies[i].x/Game::TILE_SIZE]==2
             || Game::grid[(m_enemies[i].y + m_enemyPixmap.height()/2)/Game::TILE_SIZE][(m_enemies[i].x + m_enemyPixmap.width()/2)/Game::TILE_SIZE]==2)
        {
            m_isGame = false;
        }
    }

    //draw
    clear();
    setBackgroundBrush(QBrush(Qt::black));
    for (int i=0; i < Game::M; i++)
    {
        for (int j = 0; j < Game::N; j++)
        {
            if (Game::grid[i][j] == 0)
            {
                continue;
            }
            if (Game::grid[i][j]==1)
            {
                QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(m_tilePixmap);
                pixmapItem->setPos(j*Game::TILE_SIZE, i*Game::TILE_SIZE);
                addItem(pixmapItem);
            }
            if (Game::grid[i][j] == 2)
            {
                QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(m_activeTilePixmap);
                pixmapItem->setPos(j*Game::TILE_SIZE, i*Game::TILE_SIZE);
                addItem(pixmapItem);
            }
        }
    }

    QGraphicsPixmapItem *playerItem = new QGraphicsPixmapItem(m_heroPixmap);
    playerItem->setPos(m_x*Game::TILE_SIZE, m_y*Game::TILE_SIZE);
    addItem(playerItem);

    m_enemyRotation += 10.0f;

    for (int i=0; i < m_enemyCount; i++)
    {
        QGraphicsPixmapItem *enemyItem = new QGraphicsPixmapItem(m_enemyPixmap);
        enemyItem->setPos(m_enemies[i].x, m_enemies[i].y);
        enemyItem->setTransformOriginPoint(20,20);
        enemyItem->setRotation(m_enemyRotation);
        addItem(enemyItem);
    }

    if(!m_isGame)
    {
        QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_gameOverPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
        addItem(bgItem);
    }
}

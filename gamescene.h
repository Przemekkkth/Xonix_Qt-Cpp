#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPixmap>

#include "game.h"
#include "enemy.h"

class QTimer;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void update();
private:
    void loadPixmaps();
    Game m_game;
    QPixmap m_enemyPixmap, m_gameOverPixmap, m_tilesPixmap;

    int m_enemyCount;
    Enemy m_enemies[10];

    bool m_isGame;
    int m_x, m_y, m_dx, m_dy;
    float m_timer, m_delay;
    QTimer *m_gameTimer;
    bool m_moveUp, m_moveRight, m_moveDown, m_moveLeft;
    float m_enemyRotation;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H

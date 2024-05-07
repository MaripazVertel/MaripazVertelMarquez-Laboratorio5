#ifndef TIJERA_H
#define TIJERA_H

#include <QGraphicsPixmapItem>

class Tijera : public QGraphicsPixmapItem
{
public:
    Tijera(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    void move();
    void checkCollision();

private:
    qreal velocityX = 1.0;
    qreal velocityY = 1.0;
};

#endif // TIJERA_H

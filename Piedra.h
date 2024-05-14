#ifndef PIEDRA_H
#define PIEDRA_H

#include <QGraphicsPixmapItem>

class Piedra : public QGraphicsPixmapItem
{
public:
    Piedra(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    void move();
    void checkCollision();

private:
    qreal velocityX = 1.0;
    qreal velocityY = 1.0;
};

#endif // PIEDRA_H

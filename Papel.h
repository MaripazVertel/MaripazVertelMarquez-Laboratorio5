#ifndef PAPEL_H
#define PAPEL_H

#include <QGraphicsPixmapItem>

class Papel : public QGraphicsPixmapItem
{
public:
    Papel(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    void move();
    void checkCollision();

private:
    qreal velocityX = 1.0;
    qreal velocityY = 1.0;
};

#endif // PAPEL_H

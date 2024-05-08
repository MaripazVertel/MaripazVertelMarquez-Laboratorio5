#include "constants.h"
#include "Tijera.h"

Tijera::Tijera(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaledToWidth(50), parent) // Escalando la imagen al 50% del tamaño original
{}

void Tijera::move() {
    qreal newPosX = this->x() + velocityX;
    qreal newPosY = 0 + velocityY;

    // Verificar límites horizontales
    if (newPosX < 0 || newPosX > HORZLIM - this->pixmap().width()) {
        velocityX = -velocityX;
    }

    // Verificar límites verticales
    if (newPosY < 0 || newPosY > VERTLIM - this->pixmap().height()) {
        velocityY = -velocityY;
    }

    this->setPos(newPosX, newPosY);
}

void Tijera::checkCollision() {

}

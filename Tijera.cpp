#include "constants.h"
#include "Tijera.h"


void Tijera::move() {
    qreal newPosX = this->x() + velocityX;

    // Mantener la posición Y constante
    qreal newPosY = this->y();

    // Verificar límites horizontales
    if (newPosX < 0 || newPosX > HORZLIM - this->pixmap().width()) {
        velocityX = -velocityX;
    }

    this->setPos(newPosX, newPosY);
}

void Tijera::checkCollision() {

}

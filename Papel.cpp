#include "constants.h"
#include "Papel.h"

void Papel::move() {
    qreal newPosX = this->x() + velocityX;
    qreal newPosY = this->y() + velocityY;

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
void Papel::checkCollision() {

}

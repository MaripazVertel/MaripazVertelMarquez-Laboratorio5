#include "constants.h"
#include "Piedra.h"


void Piedra::move() {
    qreal newPosX = this->x(); // Mantenemos la posición en el eje X constante
    qreal newPosY = this->y() + velocityY; // Ajustamos la posición en el eje Y

        // Verificar límites verticales
        if (newPosY < 0 || newPosY > VERTLIM - this->pixmap().height()) {
            velocityY = -velocityY; // Invertimos la dirección si llegamos a un límite vertical
        }

        this->setPos(newPosX, newPosY);
    }

void Piedra::checkCollision() {

}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QPushButton>
#include "Tijera.h"
#include "Papel.h"
#include "Piedra.h"
#include <QLabel>
#include <QKeyEvent>
const int MAX_TIJERAS = 5;
const int MAX_PAPELES = 5;
const int MAX_PIEDRAS = 5;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();
    void actualizarEscena();
    void agregarTijera();
    void agregarPapel();
    void agregarPiedra();
    void detectarColisiones();
    bool colisionTijeraPiedra(Tijera* tijera, Piedra* piedra);
    bool colisionPiedraPapel(Piedra* piedra, Papel* papel);
    bool colisionPapelTijera(Papel* papel, Tijera* tijera);
    void on_ingresarJugador_clicked();
    void actualizarContador();
    void keyPressEvent(QKeyEvent *event) override;
    void crearObjetosAutomaticamente();
    void realizarAtaque();

private:
        Ui::MainWindow *ui;
        QTimer* timer = nullptr;
        QGraphicsScene* scene = nullptr;
        QVector<Tijera*> tijeras;
        QPushButton* agregarTijeraButton = nullptr;
        QPointF generateRandomPosition();
        QPointF generatePositionForNewTijera(Tijera* nuevaTijera);
        static const qreal ESPACIO_ENTRE_TIJERAS;
        QVector<Papel*> papeles;
        QPushButton* agregarPapelButton = nullptr;
        QPointF generatePositionForNewPapel(Papel* nuevaPapel);
        static const qreal ESPACIO_ENTRE_PAPELES;
        QVector<Piedra*> piedras;
        QPushButton* agregarPiedraButton = nullptr;
        QPointF generatePositionForNewPiedra(Piedra* nuevaPiedra);
        static const qreal ESPACIO_ENTRE_PIEDRAS;
        int tijerasEliminadas;
        int papelesEliminados;
        int piedrasEliminadas;
        QLabel *tijerasEliminadasLabel;
        QLabel *piedrasEliminadasLabel;
        QLabel *papelesEliminadasLabel;
        void actualizarConteo();


        QGraphicsPixmapItem* mira = nullptr;
        QLabel* contadorLabel = nullptr;
        QTimer* contadorTimer = nullptr;
        int tiempoRestante;

        int puntosJugador;  // Contador de puntos del jugador
        QLabel* puntosJugadorLabel;


};

#endif // MAINWINDOW_H

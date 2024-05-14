#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QPushButton>
#include "Tijera.h"
#include "Papel.h"
#include "Piedra.h"
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

};

#endif // MAINWINDOW_H

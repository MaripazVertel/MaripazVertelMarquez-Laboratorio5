#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QPushButton>
#include "Tijera.h"

const int MAX_TIJERAS = 5;

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

private:
    Ui::MainWindow *ui;
    QTimer* timer = nullptr;
    QGraphicsScene* scene = nullptr;
    QVector<Tijera*> tijeras;
    QPushButton* agregarTijeraButton = nullptr;
    QPointF generateRandomPosition();
};

#endif // MAINWINDOW_H

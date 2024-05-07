#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    // Crear la tijera y asignar la imagen
    QPixmap tijeraPixmap(":/tijera.png");
    tijera = new Tijera(tijeraPixmap);

    scene->setSceneRect(0, 0, HORZLIM, VERTLIM);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(scene->width() + 5, scene->height() + 5);
    this->resize(ui->graphicsView->width() + 100, ui->graphicsView->height() + 100);

    scene->addItem(tijera);
    // Asignar posición inicial de la tijera
    tijera->setPos(50, 50);

    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarEscena()));
}

MainWindow::~MainWindow()
{
    delete timer;
    delete tijera;
    delete scene;
    delete ui;
}

void MainWindow::on_start_clicked()
{
    timer->start(20);
}

void MainWindow::actualizarEscena() {
    tijera->move();
    tijera->checkCollision();
}

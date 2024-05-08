#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Botón para agregar tijeras
    agregarTijeraButton = new QPushButton("Agregar Tijera", this);
    connect(agregarTijeraButton, &QPushButton::clicked, this, &MainWindow::agregarTijera);
    ui->verticalLayout->addWidget(agregarTijeraButton);

    timer->stop();
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);
}

MainWindow::~MainWindow()
{
    delete timer;
    for (Tijera* tijera : tijeras)
        delete tijera;
    delete scene;
    delete ui;
}

void MainWindow::on_start_clicked()
{
    timer->start(20);
}

void MainWindow::actualizarEscena()
{
    for (Tijera* tijera : tijeras) {
        tijera->move();
        tijera->checkCollision();
    }
}

void MainWindow::agregarTijera()
{
    if (tijeras.size() < MAX_TIJERAS) {
        QPixmap tijeraPixmap(":/tijera.png");
        Tijera* nuevaTijera = new Tijera(tijeraPixmap);
        nuevaTijera->setPos(generateRandomPosition());
        scene->addItem(nuevaTijera);
        tijeras.append(nuevaTijera);
    }
}


QPointF MainWindow::generateRandomPosition()
{
    qreal x = QRandomGenerator::global()->bounded(scene->width() - TIJERA_SIZE.width());
    qreal y = QRandomGenerator::global()->bounded(scene->height() - TIJERA_SIZE.height());
    return QPointF(x, y);
}

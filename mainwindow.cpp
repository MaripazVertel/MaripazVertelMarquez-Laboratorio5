#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QRandomGenerator>
#include "constants.h"
#include "Tijera.h"

const qreal MainWindow::ESPACIO_ENTRE_TIJERAS = 200;

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


Tijera::Tijera(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaledToWidth(40), parent)
{}

void MainWindow::agregarTijera()
{
    int desplazamiento = 50; // Asumiendo un desplazamiento constante entre cada par de tijeras
    if (tijeras.size() < MAX_TIJERAS) {
        QPixmap tijeraPixmap(":/tijera.png");
        Tijera* nuevaTijera = new Tijera(tijeraPixmap);
        // Calcular la posición basándose en el índice y el desplazamiento
        qreal x = tijeras.size() * desplazamiento;
        qreal y = tijeras.size() * desplazamiento;
        nuevaTijera->setPos(QPointF(x, y));
        scene->addItem(nuevaTijera);
        tijeras.append(nuevaTijera);
    }
}


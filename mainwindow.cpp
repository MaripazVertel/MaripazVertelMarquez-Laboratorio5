#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QRandomGenerator>
#include "constants.h"
#include "Tijera.h"
#include "Papel.h"
#include "Piedra.h"

const qreal MainWindow::ESPACIO_ENTRE_TIJERAS = 200;
const qreal MainWindow::ESPACIO_ENTRE_PAPELES= 200;
const qreal MainWindow::ESPACIO_ENTRE_PIEDRAS= 200;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tijerasEliminadas(0)
    , papelesEliminados(0)
    , piedrasEliminadas(0)



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

    // Botón para agregar papel
    agregarPapelButton = new QPushButton("Agregar Papel", this);
    connect(agregarPapelButton, &QPushButton::clicked, this, &MainWindow::agregarPapel);
    ui->verticalLayout->addWidget(agregarPapelButton);

    timer->stop();
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);

    // Botón para agregar piedra
    agregarPiedraButton = new QPushButton("Agregar Piedra", this);
    connect(agregarPiedraButton, &QPushButton::clicked, this, &MainWindow::agregarPiedra);
    ui->verticalLayout->addWidget(agregarPiedraButton);

    // Etiquetas para el conteo de eliminaciones
    tijerasEliminadasLabel = new QLabel("Tijeras eliminadas: 0", this);
    piedrasEliminadasLabel = new QLabel("Piedras eliminadas: 0", this);
    papelesEliminadasLabel = new QLabel("Papeles eliminados: 0", this);
    ui->verticalLayout->addWidget(tijerasEliminadasLabel);
    ui->verticalLayout->addWidget(piedrasEliminadasLabel);
    ui->verticalLayout->addWidget(papelesEliminadasLabel);

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

    delete timer;
    for (Papel* papel : papeles)
        delete papel;
    delete scene;
    delete ui;

    delete timer;
    for (Piedra* piedra : piedras)
        delete piedra;
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

    }

    for (Papel* papel :papeles){
        papel->move();

    }

    for (Piedra* piedra :piedras){
        piedra->move();

    }

    detectarColisiones();
}

void MainWindow::actualizarConteo() {
    tijerasEliminadasLabel->setText("Tijeras eliminadas: " + QString::number(tijerasEliminadas));
    piedrasEliminadasLabel->setText("Piedras eliminadas: " + QString::number(piedrasEliminadas));
    papelesEliminadasLabel->setText("Papeles eliminados: " + QString::number(papelesEliminados));
}



Tijera::Tijera(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaledToWidth(40), parent)
{}

Papel::Papel(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaledToWidth(40), parent)
{}

Piedra::Piedra(const QPixmap &pixmap, QGraphicsItem *parent)
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

void MainWindow::agregarPapel()
{
    int desplazamiento = 50; // Asumiendo un desplazamiento constante entre cada par de tijeras
    if (papeles.size() < MAX_PAPELES) {
        QPixmap papelPixmap(":/papel.png");
        Papel* nuevaPapel = new Papel(papelPixmap);
        // Calcular la posición basándose en el índice y el desplazamiento
        qreal x = papeles.size() * desplazamiento;
        qreal y = papeles.size() * desplazamiento;
        nuevaPapel->setPos(QPointF(x, y));
        scene->addItem(nuevaPapel);
        papeles.append(nuevaPapel);
    }
}


void MainWindow::agregarPiedra()
{
    int desplazamiento = 50; // Asumiendo un desplazamiento constante entre cada par de tijeras
    if (piedras.size() < MAX_PIEDRAS) {
        QPixmap piedraPixmap(":/piedra.png");
        Piedra* nuevaPiedra = new Piedra(piedraPixmap);
        // Calcular la posición basándose en el índice y el desplazamiento
        qreal x = piedras.size() * desplazamiento;
        qreal y = piedras.size() * desplazamiento;
        nuevaPiedra->setPos(QPointF(x, y));
        scene->addItem(nuevaPiedra);
        piedras.append(nuevaPiedra);
    }
}



bool MainWindow::colisionTijeraPiedra(Tijera* tijera, Piedra* piedra) {
    return tijera->collidesWithItem(piedra);
}

bool MainWindow::colisionPiedraPapel(Piedra* piedra, Papel* papel) {
    return piedra->collidesWithItem(papel);
}

bool MainWindow::colisionPapelTijera(Papel* papel, Tijera* tijera) {
    return papel->collidesWithItem(tijera);
}

void MainWindow::detectarColisiones() {
    // Crear listas de elementos a eliminar
    QList<Tijera*> tijerasParaEliminar;
    QList<Piedra*> piedrasParaEliminar;
    QList<Papel*> papelesParaEliminar;

    // Detectar colisiones entre tijeras y piedras
    for (Tijera* tijera : tijeras) {
        for (Piedra* piedra : piedras) {
            if (colisionTijeraPiedra(tijera, piedra)) {
                tijerasParaEliminar.append(tijera);
            }
        }
    }

    // Detectar colisiones entre piedras y papeles
    for (Piedra* piedra : piedras) {
        for (Papel* papel : papeles) {
            if (colisionPiedraPapel(piedra, papel)) {
                piedrasParaEliminar.append(piedra);
            }
        }
    }

    // Detectar colisiones entre papeles y tijeras
    for (Papel* papel : papeles) {
        for (Tijera* tijera : tijeras) {
            if (colisionPapelTijera(papel, tijera)) {
                papelesParaEliminar.append(papel);
            }
        }
    }

    // Eliminar tijeras colisionadas
    for (Tijera* tijera : tijerasParaEliminar) {
        scene->removeItem(tijera);
        tijeras.removeOne(tijera);
        delete tijera;
        tijerasEliminadas++;

    }

    // Eliminar piedras colisionadas
    for (Piedra* piedra : piedrasParaEliminar) {
        scene->removeItem(piedra);
        piedras.removeOne(piedra);
        delete piedra;
        piedrasEliminadas++;

    }

    // Eliminar papeles colisionados
    for (Papel* papel : papelesParaEliminar) {
        scene->removeItem(papel);
        papeles.removeOne(papel);
        delete papel;
        papelesEliminados++;

    }

    actualizarConteo();
}


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
QTimer* autoCreateTimer = nullptr;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tijerasEliminadas(0)
    , papelesEliminados(0)
    , piedrasEliminadas(0)
    , tiempoRestante(300) // 5 minutos en segundos
    , puntosJugador(0)



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


    // Botón para ingresar jugador
       QPushButton* ingresarJugadorButton = new QPushButton("Ingresar Jugador", this);
       connect(ingresarJugadorButton, &QPushButton::clicked, this, &MainWindow::on_ingresarJugador_clicked);
       ui->verticalLayout->addWidget(ingresarJugadorButton);

       // Contador
       contadorLabel = new QLabel("Tiempo restante: 5:00", this);
       ui->verticalLayout->addWidget(contadorLabel);
       contadorTimer = new QTimer(this);
       connect(contadorTimer, &QTimer::timeout, this, &MainWindow::actualizarContador);


       // Inicializar el temporizador de creación automática de objetos
       autoCreateTimer = new QTimer(this);
       connect(autoCreateTimer, &QTimer::timeout, this, &MainWindow::crearObjetosAutomaticamente);

       // Inicializar la etiqueta de puntos del jugador
       puntosJugadorLabel = new QLabel("Puntos del jugador: 0", this);
       ui->verticalLayout->addWidget(puntosJugadorLabel);

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
    delete contadorTimer;


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


void MainWindow::on_ingresarJugador_clicked()
{
    if (!mira) {
        QPixmap miraPixmap(":/mira.png");
        QPixmap scaledMiraPixmap = miraPixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        mira = new QGraphicsPixmapItem(scaledMiraPixmap);
        mira->setPos(scene->width() / 2 - mira->pixmap().width() / 2, scene->height() / 2 - mira->pixmap().height() / 2);
        scene->addItem(mira);
        tiempoRestante = 300;
        contadorTimer->start(1000);


        // Deshabilitar los botones de agregar objetos
        agregarTijeraButton->setDisabled(true);
        agregarPapelButton->setDisabled(true);
        agregarPiedraButton->setDisabled(true);

        // Iniciar el temporizador para crear objetos automáticamente cada 10 segundos
        autoCreateTimer->start(10000); // 10000 ms = 10 segundos
    }
}

void MainWindow::actualizarContador()
{
    if (tiempoRestante > 0) {
        tiempoRestante--;
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        contadorLabel->setText(QString("Tiempo restante: %1:%2")
            .arg(minutos, 2, 10, QLatin1Char('0'))
            .arg(segundos, 2, 10, QLatin1Char('0')));
    } else {
        contadorTimer->stop();
        scene->removeItem(mira);
        delete mira;
        mira = nullptr;
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (mira) {
        qreal step = 10.0;
        QRectF sceneBounds = scene->sceneRect();
        QRectF miraBounds = mira->boundingRect();
        QPointF miraPos = mira->pos();

        switch (event->key()) {
        case Qt::Key_W:
            if (miraPos.y() - step >= sceneBounds.top()) {
                mira->moveBy(0, -step);
            }
            break;
        case Qt::Key_A:
            if (miraPos.x() - step >= sceneBounds.left()) {
                mira->moveBy(-step, 0);
            }
            break;
        case Qt::Key_S:
            if (miraPos.y() + step + miraBounds.height() <= sceneBounds.bottom()) {
                mira->moveBy(0, step);
            }
            break;
        case Qt::Key_D:
            if (miraPos.x() + step + miraBounds.width() <= sceneBounds.right()) {
                mira->moveBy(step, 0);
            }
            break;
        case Qt::Key_F:
            realizarAtaque();
            break;
        default:
            QMainWindow::keyPressEvent(event);
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}



void MainWindow::crearObjetosAutomaticamente()
{
    if (tijeras.size() < MAX_TIJERAS) {
        agregarTijera();
    }
    if (papeles.size() < MAX_PAPELES) {
        agregarPapel();
    }
    if (piedras.size() < MAX_PIEDRAS) {
        agregarPiedra();
    }
}



void MainWindow::realizarAtaque()
{
    if (!mira) return;

    // Obtener la posición central de la mira
    QPointF miraCenter = mira->sceneBoundingRect().center();

    // Obtener todos los elementos en la posición central de la mira
    QList<QGraphicsItem*> items = scene->items(miraCenter);
    for (QGraphicsItem* item : items) {
        // Verificar si el item es una tijera
        if (Tijera* tijera = dynamic_cast<Tijera*>(item)) {
            scene->removeItem(tijera);
            tijeras.removeOne(tijera);
            delete tijera;
            puntosJugador++;
        }
        // Verificar si el item es un papel
        else if (Papel* papel = dynamic_cast<Papel*>(item)) {
            scene->removeItem(papel);
            papeles.removeOne(papel);
            delete papel;
            puntosJugador++;
        }
        // Verificar si el item es una piedra
        else if (Piedra* piedra = dynamic_cast<Piedra*>(item)) {
            scene->removeItem(piedra);
            piedras.removeOne(piedra);
            delete piedra;
            puntosJugador++;
        }
    }

    // Actualizar la etiqueta de puntos del jugador
    puntosJugadorLabel->setText("Puntos del jugador: " + QString::number(puntosJugador));
}

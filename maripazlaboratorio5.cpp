#include "maripazlaboratorio5.h"
#include "ui_maripazlaboratorio5.h"

MaripazLaboratorio5::MaripazLaboratorio5(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MaripazLaboratorio5)
{
    ui->setupUi(this);
}

MaripazLaboratorio5::~MaripazLaboratorio5()
{
    delete ui;
}


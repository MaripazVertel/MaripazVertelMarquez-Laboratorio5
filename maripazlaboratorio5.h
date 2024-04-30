#ifndef MARIPAZLABORATORIO5_H
#define MARIPAZLABORATORIO5_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MaripazLaboratorio5; }
QT_END_NAMESPACE

class MaripazLaboratorio5 : public QMainWindow
{
    Q_OBJECT

public:
    MaripazLaboratorio5(QWidget *parent = nullptr);
    ~MaripazLaboratorio5();

private:
    Ui::MaripazLaboratorio5 *ui;
};
#endif // MARIPAZLABORATORIO5_H

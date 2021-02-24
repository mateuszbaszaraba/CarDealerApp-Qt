#ifndef CARDEALER_H
#define CARDEALER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CarDealer; }
QT_END_NAMESPACE

class CarDealer : public QWidget
{
    Q_OBJECT

public:
    CarDealer(QWidget *parent = nullptr);
    ~CarDealer();

private:
    Ui::CarDealer *ui;
};
#endif // CARDEALER_H

#ifndef CARDEALER_H
#define CARDEALER_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class CarDealer; }
QT_END_NAMESPACE

class CarDealer : public QWidget
{
    Q_OBJECT

public:
    CarDealer(QWidget *parent = nullptr);

public slots:
    void addCar();
    void submitCar();
    void cancel();

private:
    QLineEdit *brandLine;
    QLineEdit *modelLine;
    QLineEdit *engineLine;
    QTextEdit *descriptionText;

    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;

    QString oldBrand;
    QString oldModel;
    QString oldEngine;
    QString oldDescription;

    QMap<int, QString> cars;
    int index {};
};
#endif // CARDEALER_H

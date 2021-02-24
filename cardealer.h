#ifndef CARDEALER_H
#define CARDEALER_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class CarDealer; }
QT_END_NAMESPACE

class CarDealer : public QWidget
{
    Q_OBJECT

public:
    CarDealer(QWidget *parent = nullptr);


private:
    QLineEdit *brandLine;
    QLineEdit *modelLine;
    QLineEdit *engineLine;
    QTextEdit *descriptionText;
};
#endif // CARDEALER_H

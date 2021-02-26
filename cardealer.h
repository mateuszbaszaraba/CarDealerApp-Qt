#ifndef CARDEALER_H
#define CARDEALER_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <finddialog.h>

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
    void editCar();
    void removeCar();
    void submitCar();
    void findCar();
    void cancel();
    void next();
    void previous();
    void saveToFile();
    void loadFromFile();

private:
    QLineEdit *brandLine;
    QLineEdit *modelLine;
    QLineEdit *engineLine;
    QLineEdit *indexLine;
    QTextEdit *descriptionText;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *submitButton;
    QPushButton *findButton;
    QPushButton *cancelButton;

    QPushButton *nextButton;
    QPushButton *previousButton;

    QPushButton *loadButton;
    QPushButton *saveButton;

    QString oldIndex;
    QString oldBrand;
    QString oldModel;
    QString oldEngine;
    QString oldDescription;

    QMap<QString, QString> cars;
    enum Mode { NavigationMode, AddingMode, EditingMode };
    FindDialog *dialog;

    void updateInterface(Mode mode);
    Mode currentMode;
};
#endif // CARDEALER_H

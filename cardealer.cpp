#include "cardealer.h"
#include "ui_cardealer.h"
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

CarDealer::CarDealer(QWidget *parent)
    : QWidget(parent)
{

    QLabel *brandLabel = new QLabel(tr("Brand: "));
    brandLine = new QLineEdit;
    brandLine->setReadOnly(true);

    QLabel *modelLabel = new QLabel(tr("Model: "));
    modelLine = new QLineEdit;
    modelLine->setReadOnly(true);

    QLabel *engineLabel = new QLabel(tr("Engine: "));
    engineLine = new QLineEdit;
    engineLine->setReadOnly(true);

    QLabel *descriptionLabel = new QLabel(tr("Description: "));
    descriptionText = new QTextEdit;
    descriptionText->setReadOnly(true);




    addButton = new QPushButton(tr("&Add new"));
    addButton->show();
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();

    connect(addButton, &QPushButton::clicked,
            this, &CarDealer::addCar);
    connect(submitButton, &QPushButton::clicked,
            this, &CarDealer::submitCar);
    connect(cancelButton, &QPushButton::clicked,
            this, &CarDealer::cancel);

    QHBoxLayout *buttonLayout1 = new QHBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(brandLabel, 0, 0);
    mainLayout->addWidget(brandLine, 0, 1);
    mainLayout->addWidget(modelLabel, 1, 0);
    mainLayout->addWidget(modelLine, 1, 1);
    mainLayout->addWidget(engineLabel, 2, 0);
    mainLayout->addWidget(engineLine, 2, 1);
    mainLayout->addWidget(descriptionLabel, 3, 0, Qt::AlignTop);
    mainLayout->addWidget(descriptionText, 3, 1);
    mainLayout->addLayout(buttonLayout1, 4, 1);

    setLayout(mainLayout);
    setWindowTitle("CarDealer");

}

void CarDealer::addCar()
{
    oldBrand = brandLine->text();
    oldModel = modelLine->text();
    oldEngine = engineLine->text();
    oldDescription = descriptionText->toPlainText();

    brandLine->clear();
    modelLine->clear();
    engineLine->clear();
    descriptionText->clear();

    brandLine->setReadOnly(false);
    brandLine->setFocus(Qt::OtherFocusReason);
    modelLine->setReadOnly(false);
    engineLine->setReadOnly(false);
    descriptionText->setReadOnly(false);

    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
}

void CarDealer::submitCar()
{
    QString brand = brandLine->text();
    QString model = modelLine->text();
    QString engine = modelLine->text();
    QString description = descriptionText->toPlainText();

    int in = ++index;

    if(brand.isEmpty() || model.isEmpty() || engine.isEmpty() || description.isEmpty())
    {
        QMessageBox::information(this, tr("Field is empty!"),
                                 tr("Please enter all informations"));
        return;
    }

    if(!cars.contains(in))
    {
        cars.insert(in, brand);
        index++;
        QMessageBox::information(this, tr("Add Successful"),
                                 tr("Car was added successfully"));
    } else {
        QMessageBox::information(this, tr("Add Unsuccessful"),
                                 tr("Car was not added"));
        return;
    }

    if(cars.isEmpty())
    {
        brandLine->clear();
        modelLine->clear();
        engineLine->clear();
        descriptionText->clear();
    }

    brandLine->setReadOnly(true);
    modelLine->setReadOnly(true);
    engineLine->setReadOnly(true);
    descriptionText->setReadOnly(true);
    submitButton->hide();
    cancelButton->hide();
    addButton->setEnabled(true);
}

void CarDealer::cancel()
{
    brandLine->setText(oldBrand);
    modelLine->setText(oldModel);
    engineLine->setText(oldEngine);
    descriptionText->setText(oldDescription);

    brandLine->setReadOnly(true);
    modelLine->setReadOnly(true);
    engineLine->setReadOnly(true);
    descriptionText->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}









































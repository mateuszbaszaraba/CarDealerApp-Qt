#include "cardealer.h"
#include "ui_cardealer.h"
#include <QLabel>
#include <QGridLayout>

CarDealer::CarDealer(QWidget *parent)
    : QWidget(parent)
{

    QLabel *brandLabel = new QLabel(tr("Brand: "));
    brandLine = new QLineEdit;

    QLabel *modelLabel = new QLabel(tr("Model: "));
    modelLine = new QLineEdit;

    QLabel *engineLabel = new QLabel(tr("Engine: "));
    engineLine = new QLineEdit;

    QLabel *descriptionLabel = new QLabel(tr("Description: "));
    descriptionText = new QTextEdit;



    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(brandLabel, 0, 0);
    mainLayout->addWidget(brandLine, 0, 1);
    mainLayout->addWidget(modelLabel, 1, 0);
    mainLayout->addWidget(modelLine, 1, 1);
    mainLayout->addWidget(engineLabel, 2, 0);
    mainLayout->addWidget(engineLine, 2, 1);
    mainLayout->addWidget(descriptionLabel, 3, 0, Qt::AlignTop);
    mainLayout->addWidget(descriptionText, 3, 1);

    setLayout(mainLayout);
    setWindowTitle("CarDealer");

}



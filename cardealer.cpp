#include "cardealer.h"
#include "ui_cardealer.h"

CarDealer::CarDealer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CarDealer)
{
    ui->setupUi(this);
}

CarDealer::~CarDealer()
{
    delete ui;
}


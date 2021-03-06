#include "cardealer.h"
#include "ui_cardealer.h"
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>

CarDealer::CarDealer(QWidget *parent)
    : QWidget(parent)
{



    QLabel *indexLabel = new QLabel(tr("Id: "));
    indexLine = new QLineEdit;
    indexLine->setReadOnly(true);

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


    dialog = new FindDialog(this);


    addButton = new QPushButton(tr("&Add new"));
    addButton->show();
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);
    editButton = new QPushButton(tr("&Edit"));
    editButton->show();
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->show();
    removeButton->setEnabled(false);
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();
    loadButton = new QPushButton(tr("&Load..."));
    loadButton->setToolTip(tr("Load cars from file"));
    saveButton = new QPushButton(tr("&Save"));
    saveButton->setToolTip(tr("Save to file"));

    connect(addButton, &QPushButton::clicked,
            this, &CarDealer::addCar);
    connect(editButton, &QPushButton::clicked,
            this, &CarDealer::editCar);
    connect(removeButton, &QPushButton::clicked,
            this, &CarDealer::removeCar);
    connect(submitButton, &QPushButton::clicked,
            this, &CarDealer::submitCar);
    connect(cancelButton, &QPushButton::clicked,
            this, &CarDealer::cancel);
    connect(findButton, &QPushButton::clicked,
            this, &CarDealer::findCar);
    connect(loadButton, &QPushButton::clicked,
            this, &CarDealer::loadFromFile);
    connect(saveButton, &QPushButton::clicked,
            this, &CarDealer::saveToFile);

    QHBoxLayout *buttonLayout1 = new QHBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);




    previousButton = new QPushButton(tr("Previous"));
    previousButton->setEnabled(false);
    nextButton = new QPushButton(tr("Next"));
    nextButton->setEnabled(false);

    connect(previousButton, &QPushButton::clicked,
            this, &CarDealer::previous);
    connect(nextButton, &QPushButton::clicked,
            this, &CarDealer::next);

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);




    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(indexLabel, 0, 3);
    mainLayout->addWidget(indexLine, 0, 4);
    mainLayout->addWidget(brandLabel, 0, 0);
    mainLayout->addWidget(brandLine, 0, 1);
    mainLayout->addWidget(modelLabel, 1, 0);
    mainLayout->addWidget(modelLine, 1, 1);
    mainLayout->addWidget(engineLabel, 2, 0);
    mainLayout->addWidget(engineLine, 2, 1);
    mainLayout->addWidget(descriptionLabel, 3, 0, Qt::AlignTop);
    mainLayout->addWidget(descriptionText, 3, 1);
    mainLayout->addLayout(buttonLayout1, 4, 1);
    mainLayout->addLayout(buttonLayout2, 5, 1);

    setLayout(mainLayout);
    setWindowTitle("CarDealer");


}

void CarDealer::addCar()
{
    oldIndex = indexLine->text();
    oldBrand = brandLine->text();
    oldModel = modelLine->text();
    oldEngine = engineLine->text();
    oldDescription = descriptionText->toPlainText();

    indexLine->clear();
    brandLine->clear();
    modelLine->clear();
    engineLine->clear();
    descriptionText->clear();


    updateInterface(AddingMode);
}

void CarDealer::editCar()
{
    oldIndex = indexLine->text();
    oldBrand = brandLine->text();
    updateInterface(EditingMode);
}

void CarDealer::submitCar()
{
    QString index = indexLine->text();
    QString brand = brandLine->text();
    QString model = modelLine->text();
    QString engine = modelLine->text();
    QString description = descriptionText->toPlainText();

    if(currentMode == AddingMode)
    {
        if(index.isEmpty() || brand.isEmpty())
        {
            QMessageBox::information(this, tr("Field is empty!"),
                                     tr("Please enter all informations"));
            return;
        }

        if(!cars.contains(index))
        {
            cars.insert(index, brand);
            QMessageBox::information(this, tr("Add Successful"),
                                     tr("Car was added successfully"));
        } else {
            QMessageBox::information(this, tr("Add Unsuccessful"),
                                     tr("Car was not added"));
            return;
        }

    } else if(currentMode == EditingMode)
    {
        if(oldIndex != index) {
            if(cars.contains(index)) {
                QMessageBox::information(this, tr("Edit Successful"),
                                         tr("Done"));
                cars.remove(oldIndex);
                cars.insert(index, brand);
            } else {
                QMessageBox::information(this, tr("Error"),
                                         tr("This car already exist"));
            }
        } else if (oldBrand!=brand){
            QMessageBox::information(this, tr("Edit Successful"),
                                     tr("Done"));
            cars[index] = brand;
        }
    }

    updateInterface(NavigationMode);

}

void CarDealer::cancel()
{
    indexLine->setText(oldIndex);
    brandLine->setText(oldBrand);
    modelLine->setText(oldModel);
    engineLine->setText(oldEngine);
    descriptionText->setText(oldDescription);

    updateInterface(NavigationMode);
}

void CarDealer::removeCar()
{
    QString index = indexLine->text();
    QString brand = brandLine->text();

    if (cars.contains(index)) {

           int button = QMessageBox::question(this,
               tr("Confirm Remove"),
               tr("Are you sure you?"),
               QMessageBox::Yes | QMessageBox::No);

           if (button == QMessageBox::Yes) {

               previous();
               cars.remove(index);

               QMessageBox::information(this, tr("Remove Successful"),
                   tr("Has been removed from your address book."));
           }
       }

       updateInterface(NavigationMode);
}

void CarDealer::previous()
{
    QString in = indexLine->text();
    QMap<QString, QString>::iterator i = cars.find(in);

    if(i == cars.end())
    {
        brandLine->clear();
        return;
    }

    if(i == cars.begin())
        i = cars.end();

    i--;
    indexLine->setText(i.key());
    brandLine->setText(i.value());
}

void CarDealer::next()
{
    QString in = indexLine->text();
    QMap<QString, QString>::iterator i = cars.find(in);

    if(i != cars.end())
        i++;
    if(i == cars.end())
        i = cars.begin();

    indexLine->setText(i.key());
    brandLine->setText(i.value());
}

void CarDealer::updateInterface(Mode mode)
{
    currentMode = mode;

    switch (currentMode) {

        case EditingMode:
        case AddingMode:

            indexLine->setReadOnly(false);
            indexLine->setFocus(Qt::OtherFocusReason);
            brandLine->setReadOnly(false);

            addButton->setEnabled(false);
            editButton->setEnabled(false);
            removeButton->setEnabled(false);

            nextButton->setEnabled(false);
            previousButton->setEnabled(false);

            submitButton->show();
            cancelButton->show();
            break;

       case NavigationMode:

            if(cars.isEmpty())
            {
                indexLine->clear();
                brandLine->clear();
            }

            indexLine->setReadOnly(true);
            brandLine->setReadOnly(true);

            addButton->setEnabled(true);

            int num = cars.size();
            findButton->setEnabled(num >= 1);
            editButton->setEnabled(num >= 1);
            removeButton->setEnabled(num >= 1);
            nextButton->setEnabled(num > 1);
            previousButton->setEnabled(num > 1);

            submitButton->hide();
            cancelButton->hide();
            break;

    }
}

void CarDealer::findCar()
{
    dialog->show();

    if(dialog->exec() == QDialog::Accepted)
    {
        QString carIndex = dialog->getFindText();

        if (cars.contains(carIndex))
        {
            indexLine->setText(carIndex);
            brandLine->setText(cars.value(carIndex));
        } else {
            QMessageBox::information(this, tr("not found"),
                                     tr("It is not available"));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void CarDealer::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save cars"),
                                                    tr("Cars (*.carrs);;All files(*)"));
    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to save file"),
                                     file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << cars;

    }
}

void CarDealer::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open cars"),
                                                    tr("Cars (*.carrs);;All files(*)"));

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("unable to open file"),
                                     file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        cars.clear();
        in >> cars;

        if(cars.isEmpty())
        {
            QMessageBox::information(this, tr("no cars in file"),
                                     tr("file you are attempting to open contains no cars"));
        }
        else
        {
            QMap<QString, QString>::iterator i = cars.begin();
            indexLine->setText(i.key());
            brandLine->setText(i.value());
        }
    }
    updateInterface(NavigationMode);
}






























#include "cardealer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarDealer w;
    w.show();
    return a.exec();
}

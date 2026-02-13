#include <QApplication>
#include <QMainWindow>

#include "RangeWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    RangeWidget *widget = new RangeWidget(&mainWindow);
    mainWindow.setCentralWidget(widget);
    mainWindow.show();
    return app.exec();
}

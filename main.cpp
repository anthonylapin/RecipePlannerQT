#include "mainwindow.h"
#include "recipecontext.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    RecipeContext c;
    w.show();
    return a.exec();
}

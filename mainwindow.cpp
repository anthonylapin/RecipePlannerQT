#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach(auto recipe, _recipeContext.getRecipes()) {
        ui->recipesList->addItem(recipe.getName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Recipe Planner");
    setRecipesListWidget();
}

void MainWindow::on_actionCreate_Shopping_List_triggered()
{
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete _recipeEditorDialog;
    delete ui;
}

void MainWindow::on_addRecipeButton_clicked()
{
    Recipe r;
    _recipeEditorDialog = new RecipeEditorDialog(this, &r);
    _recipeEditorDialog->show();
    if (_recipeEditorDialog->exec() == QDialog::Accepted) {
        _recipeContext.addRecipe(r);
        _recipeContext.saveChanges();
        setRecipesListWidget();
    }
}

void MainWindow::on_btnEditRecipe_clicked()
{
    int currElemId = ui->recipesList->currentRow();
    auto currElem = _recipeContext.getRecipes().at(currElemId);

    _recipeEditorDialog = new RecipeEditorDialog(this, &currElem);
    _recipeEditorDialog->show();

    if (_recipeEditorDialog->exec() == QDialog::Accepted) {
        _recipeContext.updateRecipeAt(currElemId, currElem);
        _recipeContext.saveChanges();
        setRecipesListWidget();
    }
}

void MainWindow::setRecipesListWidget() {
    ui->btnEditRecipe->setDisabled(true);
    ui->recipesList->clear();
    foreach(auto recipe, _recipeContext.getRecipes()) {
        ui->recipesList->addItem(recipe.getName());
    }
}

void MainWindow::on_recipesList_currentRowChanged(int currentRow)
{
    if (currentRow > -1) {
        ui->btnEditRecipe->setDisabled(false);
    }
}

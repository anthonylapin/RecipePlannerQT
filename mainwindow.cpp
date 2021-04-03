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

MainWindow::~MainWindow()
{
    delete _recipeEditorDialog;
    delete _shoppingCartDialog;
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_addRecipeButton_clicked()
{
    Recipe r;
    _recipeEditorDialog = new RecipeEditorDialog(this, &r, "Add Recipe");
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

void MainWindow::on_actionCreate_Shopping_List_triggered()
{
    _shoppingCartDialog = new ShoppingCartDialog(this, _recipeContext.getRecipes());
    _shoppingCartDialog->show();

    if(_shoppingCartDialog->exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Ingredients to buy", _shoppingCartDialog->getShoppingCart());
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

void MainWindow::on_btnDeleteRecipe_clicked()
{
    int currElemId = ui->recipesList->currentRow();

    if(currElemId > -1 && _recipeContext.getRecipes().count() > currElemId) {
        _recipeContext.deleteRecipe(currElemId);
        _recipeContext.saveChanges();
        QMessageBox::information(this, "Delete recipe", "Recipe was deleted successfully!");
        setRecipesListWidget();
    } else {
        QMessageBox::warning(this, "Delete recipe", "Error ocurred while deleting recipe.");
    }

}

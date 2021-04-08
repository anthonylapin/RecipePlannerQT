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

void MainWindow::setButtonsVisibility() {
    if(_recipeContext.getRecipes().count() == 0) {
        ui->btnEditRecipe->setDisabled(true);
        ui->btnDeleteRecipe->setDisabled(true);
    } else {
        ui->btnEditRecipe->setDisabled(false);
        ui->btnDeleteRecipe->setDisabled(false);
    }
}

void MainWindow::setRecipesListWidget() {
    ui->recipesList->clear();

    foreach(auto recipe, _recipeContext.getRecipes()) {
        ui->recipesList->addItem(recipe.getName());
    }
}

void MainWindow::on_addRecipeButton_clicked()
{
    Recipe r;
    _recipeEditorDialog = new RecipeEditorDialog(this, &r, "Add Recipe");
    _recipeEditorDialog->show();
    if (_recipeEditorDialog->exec() == QDialog::Accepted) {
        _recipeContext.addRecipe(r);
        _recipeContext.saveChanges();
        setButtonsVisibility();
        setRecipesListWidget();
    }
}

void MainWindow::on_btnEditRecipe_clicked()
{
    int currElemId = ui->recipesList->currentRow();

    if (currElemId >= _recipeContext.getRecipes().count() || currElemId < 0) {
        QMessageBox::warning(this, "No inregdient were selected", "No ingredient were selected");
        return;
    }

    auto currElem = _recipeContext.getRecipes().at(currElemId);

    _recipeEditorDialog = new RecipeEditorDialog(this, &currElem);
    _recipeEditorDialog->show();

    if (_recipeEditorDialog->exec() == QDialog::Accepted) {
        _recipeContext.updateRecipeAt(currElemId, currElem);
        _recipeContext.saveChanges();
        setButtonsVisibility();
        setRecipesListWidget();
    }
}

void MainWindow::on_btnDeleteRecipe_clicked()
{
    int currElemId = ui->recipesList->currentRow();

    if(currElemId >= 0 && _recipeContext.getRecipes().count() > currElemId && ui->recipesList->count() > currElemId) {
        _recipeContext.deleteRecipe(currElemId);
        _recipeContext.saveChanges();
        QMessageBox::information(this, "Delete recipe", "Recipe was deleted successfully!");
        setButtonsVisibility();
        setRecipesListWidget();
    } else {
        QMessageBox::warning(this, "Delete recipe", "Error ocurred while deleting recipe.");
    }
}

void MainWindow::on_actionCreate_Shopping_List_triggered()
{
    _shoppingCartDialog = new ShoppingCartDialog(this, _recipeContext.getRecipes());
    _shoppingCartDialog->show();

    if(_shoppingCartDialog->exec() == QDialog::Accepted) {
        QString shoppingCartStr = _shoppingCartDialog->getShoppingCart();
        QMessageBox::information(this, "Ingredients To Buy", shoppingCartStr);
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

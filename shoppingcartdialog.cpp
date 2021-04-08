#include "shoppingcartdialog.h"
#include "ui_shoppingcartdialog.h"

ShoppingCartDialog::ShoppingCartDialog(QWidget *parent, QList<Recipe> recipes) :
    QDialog(parent),
    ui(new Ui::ShoppingCartDialog)
{
    ui->setupUi(this);
    _recipes = recipes;
    initializeFields();
}

ShoppingCartDialog::~ShoppingCartDialog()
{
    delete ui;
}

void ShoppingCartDialog::initializeFields() {
    _shoppingCart.clear();
    ui->listRecipes->clear();
    ui->listShoppingCartRecipes->clear();

    foreach(Recipe recipe, _recipes) {
        ui->listRecipes->addItem(recipe.getName());
    }
}

void ShoppingCartDialog::on_btnAddToShopCart_clicked()
{
    foreach(QListWidgetItem* item, ui->listRecipes->selectedItems()) {
        ui->listShoppingCartRecipes->addItem(item->text());
    }
}

void ShoppingCartDialog::on_buttonBox_accepted()
{
    for(int i = 0; i < ui->listShoppingCartRecipes->count(); i++)
    {
        QListWidgetItem* item = ui->listShoppingCartRecipes->item(i);
        // add recipes to shopping cart
        foreach(Recipe recipe, _recipes) {
            if(recipe.getName() == item->text()) {
               addRecipeIngredientsToShoppingCart(recipe);
            }
        }
    }

    std::sort(_shoppingCart.begin(), _shoppingCart.end(), Ingredient::compare);
}

void ShoppingCartDialog::addRecipeIngredientsToShoppingCart(Recipe recipe) {
    foreach(Ingredient ingredient, recipe.getIngredients()) {
        bool exists = false;

        // if shopping cart already has such ingredient, then set ingredient quantity to sum of 2 quantites.
        for(int i = 0; i < _shoppingCart.count(); i++) {
            if(_shoppingCart[i].getName() == ingredient.getName() && _shoppingCart[i].getMeasurementValue() == ingredient.getMeasurementValue()) {
                double amount = _shoppingCart[i].getQuantity().toDouble() + ingredient.getQuantity().toDouble();
                _shoppingCart[i].setQuantity(QString::number(amount));
                exists = true;
                break;
            }
        }

        // if no such ingredient exist, just append new ingredient to the list.
        if(!exists) _shoppingCart.append(ingredient);
    }
}

QString ShoppingCartDialog::getShoppingCart() {
    QString cartStr;

    if (_shoppingCart.count() == 0) {
        cartStr = "No recipes were selected to create a shopping cart list.";
    } else {
        foreach(Ingredient ingredient, _shoppingCart) {
            cartStr = cartStr + ingredient.getShowName() + "\n";
        }
    }

    return cartStr;
}

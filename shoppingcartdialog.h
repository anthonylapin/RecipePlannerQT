#ifndef SHOPPINGCARTDIALOG_H
#define SHOPPINGCARTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "recipe.h"
#include "ingredient.h"

namespace Ui {
class ShoppingCartDialog;
}

class ShoppingCartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShoppingCartDialog(QWidget *parent = nullptr, QList<Recipe> recipes = QList<Recipe>());

    ~ShoppingCartDialog();

    QString getShoppingCart();
private slots:
    void on_btnAddToShopCart_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ShoppingCartDialog *ui;

    QList<Recipe> _recipes;

    QList<Ingredient> _shoppingCart;

    void initializeFields();

    void addRecipeIngredientsToShoppingCart(Recipe recipe);

};

#endif // SHOPPINGCARTDIALOG_H

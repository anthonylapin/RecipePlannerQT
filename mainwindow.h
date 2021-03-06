#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "recipecontext.h"
#include "recipeeditordialog.h"
#include "shoppingcartdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCreate_Shopping_List_triggered();

    void on_actionExit_triggered();

    void on_addRecipeButton_clicked();

    void on_btnEditRecipe_clicked();

    void on_btnDeleteRecipe_clicked();

private:
    Ui::MainWindow *ui;

    RecipeContext _recipeContext;

    RecipeEditorDialog* _recipeEditorDialog;

    ShoppingCartDialog* _shoppingCartDialog;

    void setRecipesListWidget();

    void setButtonsVisibility();
};
#endif // MAINWINDOW_H

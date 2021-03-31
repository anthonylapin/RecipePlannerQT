#ifndef RECIPEEDITORDIALOG_H
#define RECIPEEDITORDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <recipe.h>

namespace Ui {
class RecipeEditorDialog;
}

class RecipeEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeEditorDialog(QWidget *parent = nullptr, Recipe* recipe = nullptr);
    ~RecipeEditorDialog();

private slots:

    void on_btnAddIngredient_clicked();

    void on_btnDeleteIngredient_clicked();

    void on_lineRecipeName_textChanged(const QString &arg1);

    void on_txtRecipeInstruction_textChanged();

private:
    Ui::RecipeEditorDialog *ui;
    Recipe* _recipe;

    void initializeFields();
    bool validateIngredientInput(QString name, QString amount, QString measurementVal);
};

#endif // RECIPEEDITORDIALOG_H

#include "recipeeditordialog.h"
#include "ui_recipeeditordialog.h"

RecipeEditorDialog::RecipeEditorDialog(QWidget *parent, Recipe *recipe) :
    QDialog(parent),
    ui(new Ui::RecipeEditorDialog) // pass recipe into constructor.
{
    ui->setupUi(this);

    if (recipe != nullptr) {
        setWindowTitle("Edit Recipe");
        _recipe = recipe;
        initializeFields();
    } else {
        _recipe = new Recipe();
        setWindowTitle("Add Recipe");
    }

    //ui->btnAddIngredient->setDisabled(true); // enable when ingredient input values are not empty.
    //ui->btnDeleteIngredient->setDisabled(true); // enable when ingredient input values are not empty.
}

void RecipeEditorDialog::initializeFields() {
    ui->lineRecipeName->setText(_recipe->getName());
    ui->txtRecipeInstruction->setText(_recipe->getInstruction());

    foreach(auto ingredient, _recipe->getIngredients()) {
        ui->listIngredients->addItem(ingredient.getShowName());
    }
}

RecipeEditorDialog::~RecipeEditorDialog()
{
    delete _recipe;
    delete ui;
}

void RecipeEditorDialog::on_btnAddIngredient_clicked()
{
    QString amount = ui->lineIngredientAmount->text();
    QString name = ui->lineIngredientName->text();
    QString measurementVal = ui->lineIngredientMeasurement->text();
    bool inputError = false;

    if (!QRegExp("\\d*").exactMatch(amount) || amount.isEmpty()) {
        QMessageBox::warning(this, "Ingredient input warning", "Ingredient amount value must be numeric.");
        inputError = true;
    }
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ingredient input warning", "Ingredient name value must be not empty.");
        inputError = true;
    }
    if (measurementVal.isEmpty()) {
        QMessageBox::warning(this, "Ingredient input warning", "Ingredient measurement value must be not empty.");
        inputError = true;
    }

    if (inputError) return;

    auto ingredientToAdd = Ingredient(name, amount, measurementVal);
    _recipe->addIngredient(ingredientToAdd);
    ui->listIngredients->addItem(ingredientToAdd.getShowName());
}

void RecipeEditorDialog::on_btnDeleteIngredient_clicked()
{
    int indexToDel = ui->listIngredients->currentIndex().row();
    ui->listIngredients->model()->removeRow(indexToDel);
    _recipe->removeIngredient(indexToDel);
}

void RecipeEditorDialog::on_lineRecipeName_textChanged(const QString &arg1)
{
    _recipe->setName(arg1);
}

void RecipeEditorDialog::on_txtRecipeInstruction_textChanged()
{
    _recipe->setInstruction(ui->txtRecipeInstruction->toPlainText());
}

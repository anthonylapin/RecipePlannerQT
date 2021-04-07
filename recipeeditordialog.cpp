#include "recipeeditordialog.h"
#include "ui_recipeeditordialog.h"

RecipeEditorDialog::RecipeEditorDialog(QWidget *parent, Recipe *recipe, QString title) :
    QDialog(parent),
    ui(new Ui::RecipeEditorDialog) // pass recipe into constructor.
{
    ui->setupUi(this);

    _recipe = recipe;

    initializeFields();

    setWindowTitle(title);

    setOkButtonEnability();
}

RecipeEditorDialog::~RecipeEditorDialog()
{
    delete _recipe;
    delete ui;
}

void RecipeEditorDialog::initializeFields() {
    ui->lineRecipeName->setText(_recipe->getName());
    ui->txtRecipeInstruction->setText(_recipe->getInstruction());
    initializeIngredientList();
    clearIngredientInputFields();
}

void RecipeEditorDialog::initializeIngredientList() {
    ui->listIngredients->clear();
    foreach(auto ingredient, _recipe->getIngredients()) {
        ui->listIngredients->addItem(ingredient.getShowName());
    }
}

void RecipeEditorDialog::clearIngredientInputFields() {
    ui->lineIngredientAmount->clear();
    ui->lineIngredientMeasurement->clear();
    ui->lineIngredientName->clear();
}

void RecipeEditorDialog::on_btnAddIngredient_clicked()
{
    QString name = ui->lineIngredientName->text();
    QString amount = ui->lineIngredientAmount->text();
    QString measurementVal = ui->lineIngredientMeasurement->text();

    if (validateIngredientInput(name, amount, measurementVal)) return;

    double amountNumeric = amount.toDouble();

    int indexOfIngredient = _recipe->findIngredient(name, measurementVal);

    if(indexOfIngredient >= 0) {
        QList<Ingredient> ingredients = _recipe->getIngredients();
        amountNumeric += ingredients[indexOfIngredient].getQuantity().toDouble();
        Ingredient ingredientToUpdate = Ingredient(name, QString::number(amountNumeric), measurementVal);
        _recipe->updateIngredientAt(indexOfIngredient, ingredientToUpdate);
    } else {
        Ingredient ingredientToAdd = Ingredient(name, QString::number(amountNumeric), measurementVal);
        _recipe->addIngredient(ingredientToAdd);
        ui->listIngredients->addItem(ingredientToAdd.getShowName());
    }

    clearIngredientInputFields();
    initializeIngredientList();
}

bool RecipeEditorDialog::validateIngredientInput(QString name, QString amount, QString measurementVal) {
    bool inputError = false;
    bool validateAmount;

    double amountNumeric = amount.toDouble(&validateAmount);

    if (!validateAmount || amountNumeric <= 0) {
        QMessageBox::warning(this, "Ingredient input warning", "Ingredient amount value must be numeric and greater than 0.");
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

    return inputError;
}

void RecipeEditorDialog::on_btnDeleteIngredient_clicked()
{
    int indexToDel = ui->listIngredients->currentIndex().row();
    if (indexToDel >= 0 && ui->listIngredients->count() > indexToDel && _recipe->getIngredients().count() > indexToDel) {
        ui->listIngredients->model()->removeRow(indexToDel);
        _recipe->removeIngredient(indexToDel);
    }
}

void RecipeEditorDialog::on_lineRecipeName_textChanged(const QString &arg1)
{
    _recipe->setName(arg1);
    setOkButtonEnability();
}

void RecipeEditorDialog::on_txtRecipeInstruction_textChanged()
{
    _recipe->setInstruction(ui->txtRecipeInstruction->toPlainText());
    setOkButtonEnability();
}

void RecipeEditorDialog::setOkButtonEnability() {
    if(ui->lineRecipeName->text() == "" || ui->txtRecipeInstruction->toPlainText() == "") {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

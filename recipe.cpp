#include "recipe.h"

Recipe::Recipe()
{
}

Recipe::Recipe(QString name, QString instruction) {
    setName(name);
    setInstruction(instruction);
}

QString Recipe::getName() {
    return _name;
}

QString Recipe::getInstruction() {
    return _instruction;
}


QList<Ingredient> Recipe::getIngredients() {
    return _ingredients;
}

void Recipe::setName(QString name) {
    _name = name;
}

void Recipe::setInstruction(QString instruction) {
    _instruction = instruction;
}

void Recipe::setIngredients(QList<Ingredient> ingredients) {
    _ingredients = ingredients;
}

void Recipe::addIngredient(Ingredient ingredient) {
    _ingredients.append(ingredient);
}

void Recipe::removeIngredient(int index) {
    _ingredients.removeAt(index);
}

void Recipe::updateIngredientAt(int index, Ingredient ingredient) {
    _ingredients.replace(index, ingredient);
}

int Recipe::findIngredient(QString name, QString measurementVal) {
    for (int i = 0; i < _ingredients.count(); i++) {
        if(_ingredients[i].getName() == name && _ingredients[i].getMeasurementValue() == measurementVal) {
            return i;
        }
    }

    return -1;
}

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

void Recipe::addIngredient(Ingredient ingredient) {
    _ingredients.append(ingredient);
}

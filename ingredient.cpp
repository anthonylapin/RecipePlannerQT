#include "ingredient.h"

Ingredient::Ingredient()
{

}

Ingredient::Ingredient(QString name, QString quantity)
{
    _name = name;
    _quantity = quantity;
}

QString Ingredient::getName() {
    return _name;
}

QString Ingredient::getQuantity() {
    return _quantity;
}

#include "ingredient.h"

Ingredient::Ingredient()
{
    _name = "";
    _quantity = "";
    _measurementValue = "";
}

Ingredient::Ingredient(QString name, QString quantity, QString measurementValue)
{
    _name = name;
    _quantity = quantity;
    _measurementValue = measurementValue;
}

QString Ingredient::getName() {
    return _name;
}

QString Ingredient::getQuantity() {
    return _quantity;
}

QString Ingredient::getMeasurementValue() {
    return _measurementValue;
}

QString Ingredient::getShowName() {
    return _name + " " + _quantity + " " + _measurementValue;
}

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>
#include <QJsonObject>

class Ingredient
{
public:
    Ingredient();
    Ingredient(QString name, QString quantity, QString measurementVal);
    QString getName();
    QString getQuantity();
    QString getMeasurementValue();
    QString getShowName();
private:
    QString _name;
    QString _quantity;
    QString _measurementValue;
};

#endif // INGREDIENT_H

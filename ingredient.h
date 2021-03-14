#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>
#include <QJsonObject>

class Ingredient
{
public:
    Ingredient();
    Ingredient(QString name, QString quantity);
    QString getName();
    QString getQuantity();
private:
    QString _name;
    QString _quantity;
};

#endif // INGREDIENT_H

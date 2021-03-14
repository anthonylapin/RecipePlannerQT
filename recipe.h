#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QList>
#include "ingredient.h"

class Recipe
{
public:
    Recipe();
    Recipe (QString name, QString instruction);
private:
    QString _name;
    QString _instruction;
    QList<Ingredient> _ingredients;
};

#endif // RECIPE_H

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

    QString getName();
    QString getInstruction();
    QList<Ingredient> getIngredients();

    void setName(QString name);
    void setInstruction(QString instruction);
    void setIngredients(QList<Ingredient> ingredients);

    void addIngredient(Ingredient ingredient);
    void removeIngredient(int index);
private:
    QString _name;
    QString _instruction;
    QList<Ingredient> _ingredients;
};

#endif // RECIPE_H

#ifndef RECIPECONTEXT_H
#define RECIPECONTEXT_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QList>
#include "recipe.h"

class RecipeContext
{
public:
    RecipeContext();

private:
    QList<Recipe> _recipes;

    QJsonDocument readJsonDocument(QString fileName);
    QString getRecipesFilePath();
    QJsonArray getRecipesJsonArray();
    void initializeRecipesList();
};

#endif // RECIPECONTEXT_H

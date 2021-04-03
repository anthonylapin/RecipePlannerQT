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

    QList<Recipe> getRecipes();

    void updateRecipeAt(int index, Recipe recipe);

    void addRecipe(Recipe recipe);

    void deleteRecipe(int index);

    void saveChanges();
private:
    QList<Recipe> _recipes;

    QJsonDocument readJsonDocument(QString fileName);

    QString getRecipesFilePath();

    QJsonArray getRecipesJsonArray();

    void initializeRecipesList();

    Ingredient parseJsonIngredient(QJsonObject ingredientJson);

    Recipe parseJsonRecipe(QJsonObject recipeJson);

    void saveChangesToJsonFile(QJsonDocument doc);

    QJsonDocument parseRecipesToJsonDocument();
};

#endif // RECIPECONTEXT_H

#include "recipecontext.h"

RecipeContext::RecipeContext()
{
    initializeRecipesList();
}

QJsonDocument RecipeContext::readJsonDocument(QString fileName) {
    QFile file;
    file.setFileName(fileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!file.isOpen()) {
        return QJsonDocument::fromJson("");
    }

    QString content = file.readAll();
    file.close();

    return QJsonDocument::fromJson(content.toUtf8());
}

QString RecipeContext::getRecipesFilePath() {
    QJsonDocument configDoc = readJsonDocument(":/new/static/config.json");
    QJsonObject configObj = configDoc.object();
    return configObj["recipesPath"].toString();
}

QJsonArray RecipeContext::getRecipesJsonArray() {
    QString path = getRecipesFilePath();
    QJsonDocument recipesDoc = readJsonDocument(path);
    return recipesDoc.array();
}

Ingredient RecipeContext::parseJsonIngredient(QJsonObject ingredientJson) {
    QString name = ingredientJson["name"].toString();
    QString quantity = ingredientJson["quantity"].toString();
    QString measurementVal = ingredientJson["measurementValue"].toString();
    return Ingredient(name, quantity, measurementVal);
}

Recipe RecipeContext::parseJsonRecipe(QJsonObject recipeJson) {
    Recipe recipe;

    recipe.setName(recipeJson["name"].toString());
    recipe.setInstruction(recipeJson["instruction"].toString());

    QJsonArray ingredientsJson = recipeJson["ingredients"].toArray();
    for(auto&& ingredientRef : ingredientsJson) {
        QJsonObject ingredientJson = ingredientRef.toObject();
        Ingredient ingredient = parseJsonIngredient(ingredientJson);
        recipe.addIngredient(ingredient);
    }

    return recipe;
}

void RecipeContext::initializeRecipesList() {
    QJsonArray recipesJsonArr = getRecipesJsonArray();
    for(auto&& recipeJsonRef : recipesJsonArr) {
        QJsonObject recipeJson = recipeJsonRef.toObject();
        Recipe recipe = parseJsonRecipe(recipeJson);
        _recipes.append(recipe);
    }
}

QList<Recipe> RecipeContext::getRecipes() {
    return _recipes;
}

void RecipeContext::updateRecipeAt(int index, Recipe recipe) {
    _recipes.replace(index, recipe);
}

void RecipeContext::addRecipe(Recipe recipe) {
    _recipes.append(recipe);
}

QJsonDocument RecipeContext::parseRecipesToJsonDocument() {
    QJsonArray recipesJsonArr;

    foreach(Recipe recipe, _recipes) {
        QJsonObject recipeJson;

        QJsonArray ingredientsJson;
        foreach(Ingredient ingredient, recipe.getIngredients()) {
            QJsonObject ingredientJson;
            ingredientJson.insert("name", ingredient.getName());
            ingredientJson.insert("quantity", ingredient.getQuantity());
            ingredientJson.insert("measurementValue", ingredient.getMeasurementValue());

            ingredientsJson.append(ingredientJson);
        }

        recipeJson.insert("name", recipe.getName());
        recipeJson.insert("instruction", recipe.getInstruction());
        recipeJson.insert("ingredients", ingredientsJson);

        recipesJsonArr.append(recipeJson);
    }

    QJsonDocument db;
    db.setArray(recipesJsonArr);
    return db;
}

void RecipeContext::saveChangesToJsonFile(QJsonDocument doc) {
    QString fileName = getRecipesFilePath();
    QFile::resize(fileName, 0);
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite);
    file.write(doc.toJson());
    file.close();
}

void RecipeContext::saveChanges() {
   QJsonDocument doc = parseRecipesToJsonDocument();
   saveChangesToJsonFile(doc);
}

void RecipeContext::deleteRecipe(int index) {
    _recipes.removeAt(index);
}

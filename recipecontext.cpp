#include "recipecontext.h"

RecipeContext::RecipeContext()
{
    initializeRecipesList();

//    QJsonObject o = arr[0].toObject();

//    qWarning() << o["name"].toString();

//    QJsonArray ingredients = o["ingredients"].toArray();
//    QJsonObject ingredient = ingredients[1].toObject();
//    qWarning() << ingredient["name"].toString();
}

QJsonDocument RecipeContext::readJsonDocument(QString fileName) {
    QFile file;
    file.setFileName(fileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
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

void RecipeContext::initializeRecipesList() {
    QJsonArray recipesJsonArr = getRecipesJsonArray();
    for(auto&& item : recipesJsonArr) {
        QJsonObject obj = item.toObject();
        Recipe recipe;

        qWarning() << obj["name"].toString();
        qWarning() << obj["instruction"].toString();
        QJsonArray ingredients = obj["ingredients"].toArray();
        for(auto&& ingredient : ingredients) {
            QJsonObject ing = ingredient.toObject();
            qWarning() << ing["name"].toString() << ing["quantity"].toString();;
        }
    }
}

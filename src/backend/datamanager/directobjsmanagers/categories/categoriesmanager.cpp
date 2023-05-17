#include "categoriesmanager.h"

CategoriesManager::CategoriesManager(DatabaseCodes::Names databaseName,
                                     std::shared_ptr<DataClient> dataClient_)
    : OverallManager(databaseName, dataClient_)
{}

Category CategoriesManager::generateInstance(const json &genson) const
{
    Category category;
    initObject(category.id, category.content, category.creationDate, category.title);
    return category;
}

void CategoriesManager::update(const Category &object)
{
    updateObject(object.id.get(), object.creationDate, object.title, object.content);
}

void CategoriesManager::add(const Category &object)
{
    addObject(object.creationDate, object.title, object.content);
}

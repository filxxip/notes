#include "categoriesmanager.h"

CategoriesManager::CategoriesManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("notes", dataClient_)
{}

Category CategoriesManager::generateInstance(const json &genson) const
{
    Category category;
    category.id.setBaseOnJson(genson);
    category.content.setBaseOnJson(genson);
    category.creationDate.setBaseOnJson(genson);
    category.title.setBaseOnJson(genson);
    return category;
}

void CategoriesManager::update(const Category &object)
{
    setAdditionUpdateParameter(object.creationDate, OverallManagerMethods::datetimeToQString);
    setAdditionUpdateParameter(object.title);
    setAdditionUpdateParameter(object.content);
    dataClient->update(generatePath(object.id.get()));
}

void CategoriesManager::add(const Category &object)
{
    setAdditionAddParameter(object.creationDate, OverallManagerMethods::datetimeToQString);
    setAdditionAddParameter(object.title);
    setAdditionAddParameter(object.content);
    dataClient->add(UrlPath(name));
}

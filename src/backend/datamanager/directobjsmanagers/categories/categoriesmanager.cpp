#include "categoriesmanager.h"

CategoriesManager::CategoriesManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("categories", dataClient_)
{}

//std::optional<Category> CategoriesManager::get(int index) const
//{
//    std::optional<json> content = dataClient->get(generatePath(index));
//    if (content.has_value()) {
//        auto contentValue = content.value();
//        Category category;
//        category.id = OverallManagerMethods::getContentStrValue(contentValue, "id");
//        category.name = OverallManagerMethods::getContentStrValue(contentValue, "name");
//        category.color = OverallManagerMethods::getContentStrValue(contentValue, "color");
//        category.creationDate = OverallManagerMethods::getContentStrValue(contentValue,
//                                                                          "creationDate");
//        return category;
//    }
//    return {};
//}

Category CategoriesManager::generateInstance(const json &contentValue) const
{
    Category category;
    category.id = OverallManagerMethods::getContentStrValue(contentValue, "id");
    category.name = OverallManagerMethods::getContentStrValue(contentValue, "name");
    category.color = OverallManagerMethods::getContentStrValue(contentValue, "color");
    category.creationDate = OverallManagerMethods::getContentStrValue(contentValue, "creationDate");
    return category;
}

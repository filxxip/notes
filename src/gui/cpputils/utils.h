#pragma once
#include <QString>
#include "../../backend/datamanager/directobjsmanagers/overallmanager.h"
#include "../modelutils/customlistmodel.h"
#include <initializer_list>

namespace Messages {
constexpr const char *INVALID_KEYWORD = "Keyword passed as parameter is invalid.";
}

namespace DatabaseCodes {
constexpr const char *MALE = "male";
constexpr const char *FEMALE = "female";
} // namespace DatabaseCodes

namespace Validators {

bool fieldsValidator(std::initializer_list<QString *> container);

bool passwordValidator(const QString &password);

bool emailValidator(const QString &email);

} // namespace Validators

namespace DatabaseUtilsFunctions {

template<typename IdEnum, typename StructType>
std::optional<int> convertCodeToIndex(int code,
                                      QPointer<CustomListModel<StructType, IdEnum>> model,
                                      IdEnum idEnum,
                                      const QString &potentialErrorMessage = "")
{
    auto size = model->rowCount();
    for (int index = 0; index < size; index++) {
        if (model->data(index, idEnum) == code) {
            return index;
        }
    }
    if (!potentialErrorMessage.isEmpty()) {
        qDebug() << potentialErrorMessage;
    }
    return std::nullopt;
}

} // namespace DatabaseUtilsFunctions

namespace DatabaseSupportMethods {

template<typename Value, typename DataObject>
std::optional<int> getElementsWithGivenValue(const OverallManager<DataObject> &manager,
                                             const std::string &keyword,
                                             Value value)
{
    auto searchedElements = manager.getFiltered({{keyword, value}});
    if (searchedElements.has_value()) {
        return searchedElements->size();
    }
    qDebug() << Messages::INVALID_KEYWORD;
    return std::nullopt;
}

} // namespace DatabaseSupportMethods

namespace DateStringAlternatives {
const QVector<QString> monthsNames = {"January",
                                      "February",
                                      "March",
                                      "April",
                                      "May",
                                      "June",
                                      "July",
                                      "August",
                                      "September",
                                      "October",
                                      "November",
                                      "December"};

QString convertToStringFormat(const QDate &date);
} // namespace DateStringAlternatives

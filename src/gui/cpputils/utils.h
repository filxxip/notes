#pragma once
#include <QDate>
#include <QObject>
#include <QString>
#include "../modelutils/customlistmodel.h"
#include <functional>
#include <initializer_list>

namespace Messages {
constexpr const char *INVALID_KEYWORD = "Keyword passed as parameter is invalid.";
constexpr const char *INVALID_RADIO_BUTTON = "Something is wrong with your radiobutton, check it!";
}

namespace DatabaseCodes {
constexpr const char *MALE = "male";
constexpr const char *FEMALE = "female";

enum class Names {
    PEOPLE,
    CATEGORIES,
    NOTES,
    GUI_DIALOGS,
    PEOPLE_LOGIN,
    PEOPLE_LOGOUT,
    PEOPLE_REGISTER,
    PEOPLE_REMOVE_ACCOUNT
};
inline const std::map<Names, QString> namesMap{{Names::PEOPLE, "people"},
                                               {Names::CATEGORIES, "categories"},
                                               {Names::GUI_DIALOGS, "guidialogs"},
                                               {Names::NOTES, "notes"},
                                               {Names::PEOPLE_LOGIN, "peopleLogin"},
                                               {Names::PEOPLE_LOGOUT, "peopleLogout"},
                                               {Names::PEOPLE_REGISTER, "peopleRegister"},
                                               {Names::PEOPLE_REMOVE_ACCOUNT,
                                                "peopleRemoveAccount"}};
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

void tickWait(int interval, std::function<void()> func, QObject *parent);

} // namespace DatabaseUtilsFunctions

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

#pragma once
#include <QDate>
#include <QObject>
#include <QString>

#include "../modelutils/customlistmodel.h"
//#include "src/gui/calendar/calendarcontroller.h"
//#include "src/gui/modelutils/listmodelbuilder.h"
//#include "src/gui/radiobutton/radiobuttoncontroller.h"
//#include "src/gui/userview/entrycontroller.h"

#include <algorithm>
#include <functional>
#include <initializer_list>
template<typename T>
class OverallManager;

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
    PEOPLE_REMOVE_ACCOUNT,
    PEOPLE_GUEST
};
inline const std::map<Names, QString> namesMap{{Names::PEOPLE, "people"},
                                               {Names::CATEGORIES, "categories"},
                                               {Names::GUI_DIALOGS, "guidialogs"},
                                               {Names::NOTES, "notes"},
                                               {Names::PEOPLE_LOGIN, "peopleLogin"},
                                               {Names::PEOPLE_LOGOUT, "peopleLogout"},
                                               {Names::PEOPLE_REGISTER, "peopleRegister"},
                                               {Names::PEOPLE_GUEST, "peopleGuest"},
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

template<typename IdDataObject>
std::optional<IdDataObject> getLastObjectOfDatabase(
    const std::shared_ptr<OverallManager<IdDataObject>> &manager)
{
    auto elements = manager->get();
    if (elements.has_value()) {
        auto elemValue = elements.value();
        std::sort(std::begin(elemValue),
                  std::end(elemValue),
                  [](const auto &element1, const auto &element2) {
                      return element1.id.get() < element2.id.get();
                  });
        return *std::rbegin(elemValue);
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

constexpr const char *NAME_PLACEHOLDER = "Name...";
constexpr const char *SURNAME_PLACEHOLDER = "Surname...";
constexpr const char *EMAIL_PLACEHOLDER = "Email...";
constexpr const char *PASSWORD_PLACEHOLDER = "Password...";
constexpr const char *COUNTRY_PLACEHOLDER = "Country...";

} // namespace DateStringAlternatives

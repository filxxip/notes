#include "utils.h"
#include <QObject>
#include <QPointer>
#include <QRegularExpression>
#include <QStringLiteral>
#include <QTimer>

namespace {

const QRegularExpression emailRegex(".*@.*\\.com");

}

namespace Validators {

bool fieldsValidator(std::initializer_list<QString *> container)
{
    return std::none_of(std::begin(container), std::end(container), [](const auto data) {
        return data->isEmpty();
    });
}

bool passwordValidator(const QString &password)
{
    return std::any_of(password.begin(), password.end(), [](const QChar &ch) {
        return ch.isUpper();
    });
}

bool emailValidator(const QString &email)
{
    return emailRegex.match(email).hasMatch();
}

} // namespace Validators

namespace DateStringAlternatives {
QString convertToStringFormat(const QDate &date)
{
    return QStringLiteral("%1 %2 %3")
        .arg(QString::number(date.day()),
             DateStringAlternatives::monthsNames[date.month() - 1],
             QString::number(date.year()));
}

} // namespace DateStringAlternatives

namespace DatabaseUtilsFunctions {
void tickWait(int interval, std::function<void()> func, QObject *parent)
{
    QPointer<QTimer> myTimer = new QTimer(parent);
    myTimer->connect(myTimer, &QTimer::timeout, [func = std::move(func)] { func(); });
    myTimer->setInterval(interval);
    myTimer->start();
}

} // namespace DatabaseUtilsFunctions

namespace {
constexpr const char *FEMALE_TEXT_BUTTON = "female";
constexpr const char *MALE_TEXT_BUTTON = "male";

} // namespace

//namespace UserConfigControllerUtils2 {

//QPointer<RadioButtonController> generateRadioButton(QObject *object)
//{
//    return new RadioButtonController({RadioButtonModel(MALE_TEXT_BUTTON, true, 1),
//                                      RadioButtonModel(FEMALE_TEXT_BUTTON, false, 1)},
//                                     object);
//}

//void connectClear(EntryController *obj,
//                  QPointer<CalendarController> calendar,
//                  QPointer<RadioButtonController> radioButton)
//{
//    obj->connect(obj, &EntryController::clear, [calendar, radioButton] {
//        calendar->clear();
//        radioButton->setValue(0, true);
//    });
//}
//} // namespace UserConfigControllerUtils2

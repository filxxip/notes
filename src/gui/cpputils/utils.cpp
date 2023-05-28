#include "utils.h"
#include <QObject>
#include <QPointer>
#include <QRegularExpression>
#include <QStringLiteral>
#include <QTimer>

namespace {

const QRegularExpression emailRegex(".*@.*\\.com");

QString intToTwoLetterString(int value)
{
    auto str = QString::number(value);
    if (str.length() < 2) {
        str = "0" + str;
    }
    return str;
}
} // namespace

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

QString convertToStringFormat(const QDateTime &datetime)
{
    auto time = datetime.time();
    return QStringLiteral("%1:%2 %3")
        .arg(intToTwoLetterString(time.hour()))
        .arg(intToTwoLetterString(time.minute()))
        .arg(convertToStringFormat(datetime.date()));
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

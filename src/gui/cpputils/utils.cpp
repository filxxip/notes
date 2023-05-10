#include "utils.h"
#include <QRegularExpression>
#include <QStringLiteral>

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

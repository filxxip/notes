#include "utils.h"
#include <QRegularExpression>

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

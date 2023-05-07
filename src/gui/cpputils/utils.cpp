#include "utils.h"
#include <QRegularExpression>

namespace {

const QRegularExpression emailRegex(".*@.*\\.com");

}

namespace Validators {

template<typename PointersContainer>
void emptyFieldsValidator(PointersContainer container)
{
    return std::any_of(std::begin(container), std::end(container), [](const auto data) {
        return data->isEmpty();
    });
}

void passwordValidator(const QString &password)
{
    return std::none_of(password.begin(), password.end(), [](const QChar &ch) {
        return ch.isUpper();
    });
}

void emailValidator(const QString &email)
{
    return !emailRegex.match(email).hasMatch();
}
} // namespace Validators

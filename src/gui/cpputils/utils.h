#pragma once

namespace Validators {

template<typename PointersContainer>
void emptyFieldsValidator(PointersContainer container);

void passwordValidator(const QString &password);

void emailValidator(const QString &email);

} // namespace Validators

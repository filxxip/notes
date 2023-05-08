#pragma once
#include <QString>
#include "../modelutils/customlistmodel.h"
#include <initializer_list>

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

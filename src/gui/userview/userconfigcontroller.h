#pragma once

#include <QPointer>
#include "entrycontroller.h"

namespace UserConfigControllerUtils {
QPointer<RadioButtonController> generateRadioButton(QObject *object = nullptr);
void connectClear(EntryController *obj,
                  QPointer<CalendarController> calendar,
                  QPointer<RadioButtonController> radioButton);

template<typename EnumStatus>
QString getPartOfPerson(EnumStatus componentEnum, QPointer<UserViewListModel> model)
{
    auto index = model->indexOf(componentEnum);
    auto mydata = model->data(index, ModelStatuses::Roles::VALUE);
    return mydata.template value<QString>();
}

} // namespace UserConfigControllerUtils

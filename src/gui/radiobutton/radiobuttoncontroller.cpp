#include "radiobuttoncontroller.h"

RadioButtonController::RadioButtonController(QVector<RadioButtonModel> modelElements,
                                             QObject *parent)
    : QObject(parent)
{
    model = FastModelBuilder<RadioButtonModel, EnumStatus>(this)
                .add(EnumStatus::VALUE, &RadioButtonModel::value)
                .add(EnumStatus::TEXT, &RadioButtonModel::text)
                .add(EnumStatus::GROUP, &RadioButtonModel::group)
                .build();
    model->setEntries(std::move(modelElements));
}

void RadioButtonController::setValue(int index, bool value)
{
    this->model->setData(index, value, EnumStatus::VALUE);
    emit assign(index, value);
}

bool RadioButtonController::getValue(int index) const
{
    return model->data(index, EnumStatus::VALUE).value<bool>();
}

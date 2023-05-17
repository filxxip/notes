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
    auto currentElementGroup = model->data(index, EnumStatus::GROUP);
    if (value) {
        for (int i = 0; i < model->rowCount(); i++) {
            auto elementGroup = model->data(i, EnumStatus::GROUP);
            if (i != index && currentElementGroup != 0 && currentElementGroup == elementGroup) {
                model->setData(i, false, EnumStatus::VALUE);
            }
        }
    }
    emit assign(index, value);
}

bool RadioButtonController::getValue(int index) const
{
    return model->data(index, EnumStatus::VALUE).value<bool>();
}

bool RadioButtonController::isValid() const
{
    constexpr int groupNumber = 3;
    std::array<int, groupNumber> activation{};
    std::array<int, groupNumber> isAny{};
    for (int i = 0; i < model->rowCount(); i++) {
        auto group = model->data(i, EnumStatus::GROUP).value<int>();
        isAny[group - 1] += 1;
        if (model->data(i, EnumStatus::VALUE).value<bool>()) {
            activation[group - 1] += 1;
        }
    }
    for (int i = 0; i < groupNumber; i++) {
        if (isAny[i] > 0 && activation[i] != 1) {
            return false;
        }
    }
    return true;
}

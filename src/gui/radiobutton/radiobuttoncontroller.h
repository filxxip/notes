#pragma once

#include <QObject>
#include <QPointer>
#include "../models/radiobuttonmodel.h"
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"

class RadioButtonController : public QObject
{
    using EnumStatus = ModelStatuses::RadioButtonRoles;
    using Model = CustomListModel<RadioButtonModel, EnumStatus>;

    Q_OBJECT

    Q_PROPERTY(Model *model MEMBER model CONSTANT)

    QPointer<Model> model;

public:
    RadioButtonController(QVector<RadioButtonModel> modelElements, QObject *parent);

public:
    void setValue(int index, bool value);

    bool getValue(int index) const;

signals:
    void assign(int index, bool value);
};

#pragma once
#include <QPointer>
#include "customlistmodel.h"

template<typename ModelStructType, typename EnumRoles>
class FastModelBuilder
{
    QPointer<CustomListModel<ModelStructType, EnumRoles>> model;

public:
    FastModelBuilder(QObject *qobject = nullptr)
        : model(new CustomListModel<ModelStructType, EnumRoles>(qobject))
    {}

    template<typename ReturnType>
    FastModelBuilder &add(EnumRoles role,
                          ReturnType ModelStructType::*attributeProperty,
                          const QByteArray &name)
    {
        model->addPart(role, attributeProperty, name);
        return *this;
    }

    QPointer<CustomListModel<ModelStructType, EnumRoles>> build() { return model; }
};

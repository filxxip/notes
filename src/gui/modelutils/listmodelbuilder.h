#pragma once
#include <QPointer>
#include "../models/calendarmodel.h"
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
    FastModelBuilder &add(EnumRoles role, ReturnType ModelStructType::*attributeProperty)
    {
        model->addPart(role, attributeProperty);
        return *this;
    }

    template<typename ReturnType>
    FastModelBuilder &add(EnumRoles role,
                          std::function<const ReturnType &(const ModelStructType &)> getter,
                          std::function<void(ModelStructType &, const ReturnType &)> setter)
    {
        model->addPart(role, std::move(getter), std::move(setter));
        return *this;
    }

    //    template<typename ReturnType>
    //    FastModelBuilder &add(EnumRoles role,
    //                          std::function<const ReturnType &(const ModelStructType &)> getter)
    //    {
    //        qDebug() << "second";
    //        model->addPart(role, std::move(getter));
    //        return *this;
    //    }

    template<typename ReturnType>
    FastModelBuilder &add(EnumRoles role, std::function<ReturnType(const ModelStructType &)> getter)
    {
        model->addPart(role, std::move(getter));
        return *this;
    }

    QPointer<CustomListModel<ModelStructType, EnumRoles>> build() { return model; }
};

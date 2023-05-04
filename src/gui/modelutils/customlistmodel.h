#pragma once

#include "invokablelistmodel.h"

template<typename StructType, typename EnumData>
class CustomListModel : public AbstractListModelInvokableClass
{
protected:
    using TemplateType = StructType;

    QVector<StructType> m_data;

    QHash<int, QByteArray> names;

    QHash<EnumData, std::function<QVariant(const StructType &)>> getterActivities;

    QHash<EnumData, std::function<void(StructType &, const QVariant &)>> updateActivities;

public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setEntries(QVector<StructType> vector);

    void addEntry(T element);

    QHash<int, QByteArray> roleNames() const override;

    template<typename ReturnType>
    CustomListModel &addPart(EnumData role,
                             ReturnType StructType::*attributeProperty,
                             const QByteArray &name)
    {
        getterActivities.insert(role, makeGetterFunction(attributeProperty));
        updateActivities.insert(role, makeUpdateFunction(attributeProperty));
        names.insert(static_cast<int>(role), name);
        return *this;
    }

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant data(int index, EnumData role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    template<typename ValueType>
    bool setData(int indexvalue, const ValueType &value, EnumData role)
    {
        return setData(index(indexvalue), QVariant::fromValue(value), static_cast<int>(role));
    }
};

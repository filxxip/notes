#pragma once
#include <QAbstractListModel>
#include <functional>

#define ADD_DATA(role, name) addPart(role, &TemplateType::name, #name);

namespace {
template<typename T, typename ReturnType>
std::function<QVariant(const T &)> makeFunction(ReturnType T::*method)
{
    return [method](const T &object) {
        return QVariant::fromValue<ReturnType>(object.*method);
    }; //not the best way, there are some qtcore classes which can be initialized much faster with normal constructors
}
} // namespace

template<typename T>
class CustomListModel : public QAbstractListModel
{
protected:
    using TemplateType = T;

    QVector<T> m_data;

    QHash<int, QByteArray> names;

    QHash<int, std::function<QVariant(const T &)>> activities;

public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setEntries(QVector<T> vector);

    QHash<int, QByteArray> roleNames() const;

    template<typename ReturnType>
    CustomListModel &addPart(int role, ReturnType T::*attributeProperty, const QByteArray &name)
    {
        activities.insert(role, makeFunction(attributeProperty));
        names.insert(role, name);
        return *this;
    }

    QVariant data(const QModelIndex &index, int role) const;
};

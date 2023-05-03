#include "customlistviewmodel.h"
#include "../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "customdialog/dialogcontroller.h"
#include "log_controller.h"

AbstractListModelInvokableClass::AbstractListModelInvokableClass(QObject *object)
    : QAbstractListModel(object)
{
    model = new AdapterForQmlModelObject(this);
}

AdapterForQmlModelObject *AbstractListModelInvokableClass::get(int elementIndex)
{
    model->setCurrentIndex(index(elementIndex, 0));
    return model;
}

AdapterForQmlModelObject::AdapterForQmlModelObject(QAbstractListModel *modelPointer)
    : model(modelPointer)
    , QObject()
{}

void AdapterForQmlModelObject::setCurrentIndex(QModelIndex currentIndex)
{
    this->currentIndex = std::move(currentIndex);
}

QVariant AdapterForQmlModelObject::get(int role) const
{
    return model->data(currentIndex, role);
}

bool AdapterForQmlModelObject::update(const QVariant &variant, int role)
{
    return model->setData(currentIndex, variant, role);
}

template<typename T, typename EnumData>
CustomListModel<T, EnumData>::CustomListModel::CustomListModel(QObject *parent)
    : AbstractListModelInvokableClass(parent)
{}

template<typename T, typename EnumData>
int CustomListModel<T, EnumData>::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_data.count();
}

template<typename T, typename EnumData>
void CustomListModel<T, EnumData>::setEntries(QVector<T> vector)
{
    m_data = std::move(vector);
}

template<typename T, typename EnumData>
QHash<int, QByteArray> CustomListModel<T, EnumData>::roleNames() const
{
    return names;
}

template<typename T, typename EnumData>
QVariant CustomListModel<T, EnumData>::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count()
        || !getterActivities.contains(static_cast<EnumData>(role))) {
        return QVariant();
    }

    const T &entry = m_data.at(index.row());
    return getterActivities[static_cast<EnumData>(role)](entry);
}

template<typename T, typename EnumData>
QVariant CustomListModel<T, EnumData>::data(int index, EnumData role) const
{
    return data(this->index(index), static_cast<int>(role));
}

template<typename T, typename EnumData>
bool CustomListModel<T, EnumData>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_data.count()
        || !updateActivities.contains(static_cast<EnumData>(role))) {
        return false;
    }
    T &entry = m_data[index.row()];
    updateActivities[static_cast<EnumData>(role)](entry, value);
    emit dataChanged(index, index); // <- this does not trigger a recompution of the view
    return true;
}

template<typename T, typename EnumData>
void CustomListModel<T, EnumData>::addEntry(T element)
{
    m_data.append(std::move(element));
}

template class CustomListModel<EntryFieldModel, ModelStatuses::Roles>;
template class CustomListModel<GuiDialog, ModelStatuses::DialogRoles>;
template class CustomListModel<SwitcherModel<ModelStatuses::UserViews>,
                               ModelStatuses::UserViewsRoles>;

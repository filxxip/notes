#pragma once

#include <QColor>
#include <QObject>
#include "../customdialog/dialogcontroller.h"
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "../viewcontroller/viewcontroller.h"
#include "src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"

class CategoryController : public QObject
{
    using EnumStatus = ModelStatuses::CategoryRoles;
    using Model = CustomListModel<Category, ModelStatuses::CategoryRoles>;

    Q_OBJECT

    Q_PROPERTY(Model *model MEMBER categoryModel CONSTANT)
    Q_PROPERTY(int editedItem MEMBER editedItem NOTIFY editedItemIndexChanged)
    Q_PROPERTY(ViewController *view READ getViewController CONSTANT)

    QPointer<DialogController> dialogController;
    std::shared_ptr<AbstractViewControllerAdapter<ModelStatuses::CategoryViewTypes>>
        innerViewController;
    std::shared_ptr<CategoriesManager> manager;
    QPointer<Model> categoryModel;

    std::optional<int> owner = 2;
    int editedItem = -1; //todo z optional

    int getItemID() const;

    ViewController *getViewController() { return innerViewController->getController(); }

public:
    CategoryController(std::shared_ptr<CategoriesManager> manager_,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

    void setOwner(int id);

private slots:

    void add(const QString &name, const QColor &newColor);

    void onColorChanged(QColor color);

    void onRemove(int index);

    void onChangeName(const QString &title);

signals:
    void remove(int index);

    void editedItemIndexChanged(int index);

    void changeColor(const QColor &color);

    void changeName(const QString &text);

    void addElement(const QString &name, const QColor &newColor);
};

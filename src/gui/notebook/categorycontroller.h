#pragma once

#include <QColor>
#include <QObject>
//#include "../colorpicker/colorpicker.h"
#include "../customdialog/dialogcontroller.h"
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "../viewcontroller/viewcontroller.h"
#include "src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"

namespace {
constexpr char INVALID_INDEX_ERROR[] = "Index is out of range, check your code and fix this error.";
}

class CategoryController : public QObject
{
    using EnumStatus = ModelStatuses::CategoryRoles;
    using Model = CustomListModel<Category, ModelStatuses::CategoryRoles>;

    Q_OBJECT

    Q_PROPERTY(Model *model MEMBER categoryModel CONSTANT)
    //    Q_PROPERTY(ColorPicker *colorEditPicker MEMBER colorEditController CONSTANT)

    Q_PROPERTY(int editedItem MEMBER editedItem NOTIFY editedItemIndexChanged)
    Q_PROPERTY(ViewController *view MEMBER innerViewController CONSTANT)

    QPointer<Model> categoryModel;

    QPointer<DialogController> dialogController;
    //    QPointer<ColorPicker> colorEditController;
    QPointer<ViewController> innerViewController;
    std::optional<int> owner = 2;
    std::shared_ptr<CategoriesManager> manager;
    int editedItem = -1;

public:
    CategoryController(std::shared_ptr<CategoriesManager> manager_,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr)
        : QObject(obj)
        , manager(std::move(manager_))
        , dialogController(dialogController_)
        //        , colorEditController(new ColorPicker(this))
        , innerViewController(ViewControllerGenerators::createNonSwitcherViewContorller(
                                  ModelStatuses::CategoryViewTypes::NONE, this)
                                  ->getController())
    {
        categoryModel
            = FastModelBuilder<Category, EnumStatus>(this)
                  .add(EnumStatus::ID, &Category::id)
                  .add(EnumStatus::COLOR, &Category::color)
                  .add(EnumStatus::TITLE, &Category::title)
                  .add(EnumStatus::CREATION_DATE, &Category::creationDate)
                  .add(EnumStatus::OWNER, &Category::owner)
                  .build(manager->getFiltered({{"owner", 2}}).value());
        connect(this, &CategoryController::remove, this, &CategoryController::onRemove);
        //        connect(colorEditController, &ColorPicker::colorChanged)

        connect(this, &CategoryController::changeColor, this, &CategoryController::onColorChanged);
        connect(this, &CategoryController::changeName, this, &CategoryController::onChangeName);
    }

    void setOwner(int id) { this->owner = id; }

    Q_INVOKABLE void add(const QString &name, const QColor &newColor)
    {
        if (name.isEmpty()) {
            dialogController->showDialog(DialogCodes::UserViews::EMPTY_CATEGORY_NAME);
            return;
        }

        Category category;
        category.color = newColor.name();
        category.creationDate = QDateTime::currentDateTime();
        category.owner = owner.value();
        category.title = name;

        manager->add(category);
        categoryModel->addEntry(
            DatabaseUtilsFunctions::getLastObjectOfDatabase<Category>(manager).value());
    }

private slots:

    void onColorChanged(QColor color)
    {
        if (editedItem < 0 && editedItem >= categoryModel->rowCount()) {
            qDebug() << "todo";
            return;
        }
        auto index = categoryModel->data(editedItem, ModelStatuses::CategoryRoles::ID).value<int>();
        auto item = manager->get(index);
        if (item.has_value() && item->color.get() != color) {
            item->color = std::move(color);
            manager->update(item.value());
        }
    }

    void onRemove(int index)
    {
        if (index >= categoryModel->rowCount()) {
            qDebug() << INVALID_INDEX_ERROR;
            return;
        }
        dialogController->applyConnection([this, index](const auto &status) {
            if (status == DialogController::ActivityStatus::ACCEPT) {
                manager->remove(
                    categoryModel->data(index, ModelStatuses::CategoryRoles::ID).value<int>());
                categoryModel->removeRow(index);
                innerViewController->setUserViewType(QVariant::fromValue(
                    ModelStatuses::CategoryViewTypes::NONE)); //zmienic na adaptera
            }
        });
        dialogController->showDialog(DialogCodes::UserViews::REMOVE_CATEGORY);
    }

    void onChangeName(const QString &title)
    {
        qDebug() << title;
        qDebug() << "hello";
        if (title.isEmpty()) {
            dialogController->showDialog(DialogCodes::UserViews::EMPTY_CATEGORY_NAME);
            return;
        }
        auto index = categoryModel->data(editedItem, ModelStatuses::CategoryRoles::ID).value<int>();
        auto item = manager->get(index);
        if (item.has_value() && item->title.get() != title) {
            categoryModel->setData(editedItem, title, ModelStatuses::CategoryRoles::TITLE);
            item->title = std::move(title);
            manager->update(item.value());
        }
    }

signals:
    void remove(int index);
    void editedItemIndexChanged(int index);
    void changeColor(const QColor &color);
    void changeName(const QString &text);
};

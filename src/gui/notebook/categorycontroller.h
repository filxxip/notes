#pragma once

#include <QObject>
#include "../colorpicker/colorpicker.h"
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
    Q_PROPERTY(ColorPicker *colorEditPicker MEMBER colorEditController CONSTANT)
    Q_PROPERTY(ViewController *view MEMBER innerViewController CONSTANT)

    QPointer<Model> categoryModel;

    QPointer<DialogController> dialogController;
    QPointer<ColorPicker> colorEditController;
    QPointer<ViewController> innerViewController;
    std::optional<int> owner = 2;
    std::unique_ptr<CategoriesManager> manager;

public:
    CategoryController(std::unique_ptr<CategoriesManager> manager_,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr)
        : QObject(obj)
        , manager(std::move(manager_))
        , dialogController(dialogController_)
        , colorEditController(new ColorPicker(this))
        , innerViewController(ViewControllerGenerators::createNonSwitcherViewContorller(
                                  ModelStatuses::CategoryViewTypes::NONE, this)
                                  ->getController())
    {
        categoryModel = FastModelBuilder<Category, EnumStatus>(this)
                            .add(EnumStatus::ID, &Category::id)
                            .add(EnumStatus::COLOR, &Category::color)
                            .add(EnumStatus::TITLE, &Category::title)
                            .add(EnumStatus::CREATION_DATE, &Category::creationDate)
                            .add(EnumStatus::OWNER, &Category::owner)
                            .build(manager->getFiltered({{"owner", 2}}).value());

        connect(this, &CategoryController::remove, this, &CategoryController::onRemove);
        //        connect(colorEditController, &ColorPicker::colorChanged)
    }

    void setOwner(int id) { this->owner = id; }

    Q_INVOKABLE void add(const QString &name, const QColor &newColor)
    {
        Category category;
        category.color = newColor.name();
        category.creationDate = QDateTime::currentDateTime();
        category.owner = owner.value();
        category.title = name;

        manager->add(category);
        categoryModel->addEntry(std::move(category));
    }

private slots:
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
            }
        });
        dialogController->showDialog(DialogCodes::UserViews::REMOVE_CATEGORY);
    }

signals:
    void remove(int index);
};

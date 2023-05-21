#pragma once

#include <QObject>
#include "../customdialog/dialogcontroller.h"
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"

class CategoryController : public QObject
{
    using EnumStatus = ModelStatuses::CategoryRoles;
    using Model = CustomListModel<Category, ModelStatuses::CategoryRoles>;

    Q_OBJECT

    Q_PROPERTY(Model *model MEMBER categoryModel CONSTANT)

    QPointer<Model> categoryModel;

    QPointer<DialogController> dialogController;

public:
    CategoryController(std::unique_ptr<CategoriesManager> manager,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr)
        : QObject(obj)
        , dialogController(dialogController_)
    {
        qDebug() << "hahah";
        auto x = manager->get();
        qDebug() << x.has_value();
        categoryModel = FastModelBuilder<Category, EnumStatus>(this)
                            .add(EnumStatus::ID, &Category::id)
                            .add(EnumStatus::COLOR, &Category::color)
                            .add(EnumStatus::TITLE, &Category::title)
                            .add(EnumStatus::CREATION_DATE, &Category::creationDate)
                            .add(EnumStatus::OWNER, &Category::owner)
                            .build(manager->getFiltered({{"owner", 2}}).value());
    }
};

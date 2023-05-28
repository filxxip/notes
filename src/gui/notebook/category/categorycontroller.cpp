#include "categorycontroller.h"

namespace {
constexpr char INVALID_INDEX_ERROR[] = "Index is out of range, check your code and fix this error.";
}

CategoryController::CategoryController(std::shared_ptr<CategoriesManager> manager_,
                                       QPointer<DialogController> dialogController_,
                                       QObject *obj)
    : QObject(obj)
    , manager(std::move(manager_))
    , dialogController(dialogController_)
    , innerViewController(ViewControllerGenerators::createNonSwitcherViewContorller(
          ModelStatuses::CategoryViewTypes::NONE, this))
    , categoryModel(FastModelBuilder<Category, EnumStatus>(this)
                        .add(EnumStatus::ID, &Category::id)
                        .add(EnumStatus::COLOR, &Category::color)
                        .add(EnumStatus::TITLE, &Category::title)
                        .add(EnumStatus::CREATION_DATE, &Category::creationDate)
                        .add(EnumStatus::OWNER, &Category::owner)
                        .build())
{
    connect(this, &CategoryController::remove, this, &CategoryController::onRemove);
    connect(this, &CategoryController::changeColor, this, &CategoryController::onColorChanged);
    connect(this, &CategoryController::changeName, this, &CategoryController::onChangeName);
    connect(this, &CategoryController::addElement, this, &CategoryController::add);
}

void CategoryController::setOwner(int id)
{
    this->owner = id;
    auto filtered = manager->getFiltered({{"owner", id}});
    if (filtered.has_value()) {
        categoryModel->setEntries(filtered.value());
        return;
    }
    qDebug() << "Invalid index passed as owner, check your database!";
}

ViewController *CategoryController::getViewController()
{
    return innerViewController->getController();
}

void CategoryController::add(const QString &name, const QColor &newColor)
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

int CategoryController::getItemID(int index) const
{
    return categoryModel->data(index, ModelStatuses::CategoryRoles::ID).value<int>();
}

void CategoryController::onChangeName(const QString &title)
{
    if (title.isEmpty()) {
        dialogController->showDialog(DialogCodes::UserViews::EMPTY_CATEGORY_NAME);
        return;
    }
    auto item = manager->get(getItemID(editedItem));
    if (item.has_value() && item->title.get() != title) {
        categoryModel->setData(editedItem, title, ModelStatuses::CategoryRoles::TITLE);
        item->title = std::move(title);
        manager->update(item.value());
    }
}

void CategoryController::onRemove(int index)
{
    if (index >= categoryModel->rowCount()) {
        qDebug() << INVALID_INDEX_ERROR;
        return;
    }
    dialogController->applyConnection([this, index](const auto &status) {
        if (status == DialogController::ActivityStatus::ACCEPT) {
            manager->remove(getItemID(index));
            categoryModel->removeRow(index);
            innerViewController->setUserViewType(ModelStatuses::CategoryViewTypes::NONE);
        }
    });
    dialogController->showDialog(DialogCodes::UserViews::REMOVE_CATEGORY);
}

void CategoryController::onColorChanged(QColor color)
{
    if (editedItem < 0 && editedItem >= categoryModel->rowCount()) {
        qDebug() << INVALID_INDEX_ERROR;
        return;
    }
    auto item = manager->get(getItemID(editedItem));
    if (item.has_value() && item->color.get() != color) {
        item->color = std::move(color);
        manager->update(item.value());
    }
}

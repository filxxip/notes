#pragma once

#include <QObject>
#include "../../customdialog/dialogcontroller.h"
#include "../../statuses.h"
#include "src/backend/datamanager/directobjsmanagers/notes/notesmanager.h"

class NotesController : public QObject
{
    Q_OBJECT

    using Model = CustomListModel<Note, ModelStatuses::NoteRoles>;

    using EnumStatus = ModelStatuses::NoteRoles;

    Q_PROPERTY(Model *model MEMBER notesModel CONSTANT)

    QPointer<Model> notesModel;

    QPointer<DialogController> dialogController;

    std::shared_ptr<NotesManager> manager;

    void setModel(json genson)
    {
        qDebug() << "hellllo";
        if (auto filteredEntries = manager->getFiltered(genson); filteredEntries.has_value()) {
            auto x = filteredEntries.value();

            notesModel->setEntries(x);
            return;
        }
        qDebug() << "Filter is invalid, check yout database and try again!";
    }

public:
    NotesController(std::shared_ptr<NotesManager> manager_,
                    QPointer<DialogController> dialogController_,
                    QObject *obj = nullptr)
        : QObject(obj)
        , dialogController(dialogController_)
        , manager(manager_)
        , notesModel(FastModelBuilder<Note, EnumStatus>(this)
                         .add(EnumStatus::ID, &Note::id)
                         .add(EnumStatus::CONTENT, &Note::content)
                         .add(EnumStatus::TITLE, &Note::title)
                         .add(EnumStatus::CATEGORY, &Note::category)
                         .add(EnumStatus::RELEASE_DATE, &Note::releaseDate)
                         .add(EnumStatus::OWNER, &Note::owner)
                         .build())
    {}

    Q_INVOKABLE void setModel(int owner, int categoryIndex)
    {
        setModel({{"owner", owner}, {"category", categoryIndex}});
    }
    Q_INVOKABLE void setModel(int owner) { setModel({{"owner", owner}}); }

    Q_INVOKABLE QString getNiceDateFormat(const QDateTime &datetime) const
    {
        return DateStringAlternatives::convertToStringFormat(datetime);
    }
};

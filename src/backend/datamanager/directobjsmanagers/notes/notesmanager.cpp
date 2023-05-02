#include "notesmanager.h"

NotesManager::NotesManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("notes", dataClient_)
{}

Note NotesManager::generateInstance(const json &genson) const
{
    Note note;
    note.id.setBaseOnJson(genson);
    note.category.setBaseOnJson(genson);
    note.content.setBaseOnJson(genson);
    note.owner.setBaseOnJson(genson);
    note.releaseDate.setBaseOnJson(genson);
    note.title.setBaseOnJson(genson);
    return note;
}

void NotesManager::update(const Note &object)
{
    updateObject(object.id.get(),
                 object.category,
                 object.releaseDate,
                 object.owner,
                 object.title,
                 object.content);

    //    setAdditionUpdateParameter(object.releaseDate);
    //    setAdditionUpdateParameter(object.owner);
    //    setAdditionUpdateParameter(object.category);
    //    setAdditionUpdateParameter(object.title);
    //    setAdditionUpdateParameter(object.content);
    //    dataClient->update(generatePath(object.id.get()));
}

void NotesManager::add(const Note &object)
{
    addObject(object.category, object.releaseDate, object.owner, object.title, object.content);
}

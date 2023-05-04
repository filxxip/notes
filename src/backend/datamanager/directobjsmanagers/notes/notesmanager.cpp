#include "notesmanager.h"

NotesManager::NotesManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("notes", dataClient_)
{}

Note NotesManager::generateInstance(const json &genson) const
{
    Note note;
    initObject(genson,
               note.id,
               note.category,
               note.content,
               note.owner,
               note.releaseDate,
               note.title);
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
}

void NotesManager::add(const Note &object)
{
    addObject(object.category, object.releaseDate, object.owner, object.title, object.content);
}
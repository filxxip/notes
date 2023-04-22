#include "notesmanager.h"

NotesManager::NotesManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("notes", dataClient_)
{}

//std::optional<Note> NotesManager::get(int index) const
//{
//    std::optional<json> content = dataClient->get(generatePath(index));
//    if (content.has_value()) {
//        auto contentValue = content.value();
//        Note note;
//        note.id = QString::number(index);
//        note.title = OverallManagerMethods::getContentStrValue(contentValue, "title");
//        note.content = OverallManagerMethods::getContentStrValue(contentValue, "content");
//        note.releaseDate = OverallManagerMethods::getContentStrValue(contentValue, "releaseDate");
//        note.owner = OverallManagerMethods::getContentStrValue(contentValue, "owner");
//        note.category = OverallManagerMethods::getContentStrValue(contentValue, "category");
//        return note;
//    }
//    return {};
//}

Note NotesManager::generateInstance(const json &contentValue) const
{
    Note note;
    qDebug() << QString::fromStdString(contentValue.dump());
    note.id = OverallManagerMethods::getContentStrValue(contentValue, "id");
    note.title = OverallManagerMethods::getContentStrValue(contentValue, "title");
    note.content = OverallManagerMethods::getContentStrValue(contentValue, "content");
    note.releaseDate = OverallManagerMethods::getContentStrValue(contentValue, "releaseDate");
    note.owner = OverallManagerMethods::getContentStrValue(contentValue, "owner");
    note.category = OverallManagerMethods::getContentStrValue(contentValue, "category");
    return note;
}

#pragma once

#include "../overallmanager.h"
#include "note.h"
#include <functional>

class NotesManager final : public OverallManager<Note>
{
protected:
    Note generateInstance(const json &genson) const override;

public:
    NotesManager(QString databaseName, std::shared_ptr<DataClient> dataClient_);

    void update(const Note &object) override;

    void add(const Note &object) override;
};

#pragma once
#include "../overallmanager.h"
#include "note.h"

class NotesManager final : public OverallManager<Note>
{
public:
    NotesManager(std::shared_ptr<DataClient> dataClient_);

    std::optional<Note> get(int index) const override;
};

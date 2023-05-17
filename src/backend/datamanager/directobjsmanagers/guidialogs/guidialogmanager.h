#pragma once

#include "../overallmanager.h"
#include "guidialog.h"

class GuiDialogsManager final : public OverallManager<GuiDialog>
{
protected:
    GuiDialog generateInstance(const json &genson) const override;

public:
    GuiDialogsManager(DatabaseCodes::Names, std::shared_ptr<DataClient> dataClient_);

    void update(const GuiDialog &object) override;

    void add(const GuiDialog &object) override;
};

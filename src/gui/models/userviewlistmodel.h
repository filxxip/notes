#pragma once

#include "../modelutils/customlistmodel.h"
#include "entryfieldmodel.h"

class UserViewListModel final : public CustomListModel<EntryFieldModel, ModelStatuses::Roles>
{
public:
    UserViewListModel(QObject *parent = nullptr);

    int indexOf(ModelStatuses::PersonComponents componentEnum) const;
};

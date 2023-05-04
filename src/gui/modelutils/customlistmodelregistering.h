#pragma once

#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "../models/entryfieldmodel.h"
#include "../models/switchermodel.h"

template class CustomListModel<EntryFieldModel, ModelStatuses::Roles>;
template class CustomListModel<GuiDialog, ModelStatuses::DialogRoles>;
template class CustomListModel<SwitcherModel<ModelStatuses::UserViews>,
                               ModelStatuses::UserViewsRoles>;

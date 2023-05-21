#pragma once

#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "../calendar/calendarcontroller.h"
#include "../models/entryfieldmodel.h"
#include "../models/radiobuttonmodel.h"
#include "../models/switchermodel.h"
#include "src/backend/datamanager/directobjsmanagers/categories/category.h"

template class CustomListModel<EntryFieldModel, ModelStatuses::Roles>;
template class CustomListModel<GuiDialog, ModelStatuses::DialogRoles>;
template class CustomListModel<SwitcherModel<ModelStatuses::UserViews>,
                               ModelStatuses::UserViewsRoles>;
template class CustomListModel<Category, ModelStatuses::CategoryRoles>;
template class CustomListModel<SwitcherModel<ModelStatuses::InnerUserEditViews>,
                               ModelStatuses::UserViewsRoles>;
template class CustomListModel<CalendarModel, ModelStatuses::CalendarRoles>;
template class CustomListModel<RadioButtonModel, ModelStatuses::RadioButtonRoles>;

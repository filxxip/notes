#pragma once

#include "../categories/category.h"
#include "../guidialogs/guidialog.h"
#include "../ids/ids.h"
#include "../notes/note.h"
#include "../people/person.h"

template class OverallManager<Person>;
template class OverallManager<Note>;
template class OverallManager<Category>;
template class OverallManager<GuiDialog>;
template class OverallManager<Ids>;

#pragma once

#define REGISTER_DATA(type) \
    template class BaseData<type>; \
    template class DbData<type>; \
    template class ConstDbData<type>; \
    template class CodedDbData<type>;

REGISTER_DATA(int)
REGISTER_DATA(QString)
REGISTER_DATA(QDateTime)
REGISTER_DATA(bool)

#pragma once

#include <QDate>
#include <QObject>
#include <QVector>
#include "../models/calendarmodel.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"

namespace {

const QVector<QString> monthsNames = {"January",
                                      "February",
                                      "March",
                                      "April",
                                      "May",
                                      "June",
                                      "July",
                                      "August",
                                      "September",
                                      "October",
                                      "November",
                                      "December"};

} // namespace

class CalendarController : public QObject
{
    using EnumStatus = ModelStatuses::CalendarRoles;
    using CalendarListModel = CustomListModel<CalendarModel, EnumStatus>;

    Q_OBJECT

    Q_PROPERTY(CalendarListModel *monthModel MEMBER monthModel CONSTANT)
    Q_PROPERTY(CalendarListModel *dayModel MEMBER dayModel CONSTANT)
    Q_PROPERTY(CalendarListModel *yearModel MEMBER yearModel CONSTANT)

    QPointer<CalendarListModel> monthModel;
    QPointer<CalendarListModel> dayModel;
    QPointer<CalendarListModel> yearModel;
    QDate currentDate;

public:
    CalendarController();

signals:
    void currentDateChanged(int day, int month, int year);
    void dayChanged(int value);

private slots:

    void onCurrentDateChanged(int day, int month, int year);
};

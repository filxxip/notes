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
constexpr int DEFAULT_MAXIMUM_YEAR = 2022;
constexpr int DEFAULT_MINIMUM_YEAR = 1960;
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

    Q_PROPERTY(QString niceFormat READ getNiceDateFormat NOTIFY niceFormatChanged CONSTANT)

    QPointer<CalendarListModel> monthModel;
    QPointer<CalendarListModel> dayModel;
    QPointer<CalendarListModel> yearModel;

    int maximumYear = DEFAULT_MAXIMUM_YEAR;
    int minimumYear = DEFAULT_MINIMUM_YEAR;
    QDate currentDate = QDate(minimumYear, 1, 1);

    QString getNiceDateFormat() const;

public:
    CalendarController(QObject *obj = nullptr);

    void clear();

    void setMinMaxRange(int newMin, int newMax);

    QDateTime getCurrentDateTime() const { return QDateTime(currentDate, QTime(0, 0, 0)); }

signals:
    void resetGui();

    void currentDateChanged(int day, int month, int year);

    void niceFormatChanged(QString content);

private slots:

    void onCurrentDateChanged(int dayIndexDelta, int monthIndexDelta, int yearIndexDelta);
};

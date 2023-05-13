#pragma once

#include <QDate>
#include <QObject>
#include <QVector>
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "src/gui/models/calendarmodel.h" // @todo This way to include

namespace {
constexpr int DEFAULT_MAXIMUM_YEAR = 2022;
constexpr int DEFAULT_MINIMUM_YEAR = 1960;
} // namespace

//class HowToClass
//{
//Q_OBJECT
//Q_PROPERTY
//public:
//signals:
//public slots:
//protected slots:
//private slots:
//private:
//};

class CalendarController final : public QObject // @todo Marked as final
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

private:
    void setNewDate(int dayIndexDelta, int monthIndexDelta, int yearIndexDelta);

public:
    explicit CalendarController(QObject *obj = nullptr); // @todo Explicit here

    //    void setMinMaxRange(int newMin, int newMax);

    void changeDate(int year, int month, int day);

    QDateTime getCurrentDateTime() const { return QDateTime(currentDate, QTime(0, 0, 0)); }

signals:
    void currentDateChanged(int day, int month, int year);

    void uploadNewDate(int day, int month, int year);

    void niceFormatChanged(QString content);

public:
    Q_INVOKABLE void clear();

    Q_INVOKABLE void assignCurrent();

private slots:

    void onCurrentDateChanged(int dayIndexDelta, int monthIndexDelta, int yearIndexDelta);
};

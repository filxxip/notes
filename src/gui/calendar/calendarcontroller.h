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

private:
    void setNewDate(int dayIndexDelta, int monthIndexDelta, int yearIndexDelta)
    {
        auto day = dayIndexDelta + 1;
        auto month = monthIndexDelta + 1;
        auto year = yearIndexDelta + minimumYear;

        int begin = QDate(year, month, 1).daysInMonth();

        if (begin < dayModel->rowCount()) {
            dayModel->removeRows(begin, dayModel->rowCount() - begin);
        }

        for (int i = dayModel->rowCount() + 1; i <= begin; i++) {
            dayModel->addEntry({i, QString::number(i)});
        }

        currentDate = QDate(year, month, qMin(day, dayModel->rowCount()));
    }

public:
    CalendarController(QObject *obj = nullptr);

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

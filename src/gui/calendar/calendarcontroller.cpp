#include "calendarcontroller.h"
#include <QTimer>
#include "clockcontroller.h"

CalendarController::CalendarController(QObject *obj)
    : QObject(obj)
{
    auto initializeModel = [this](QPointer<CalendarListModel> &model) {
        model = FastModelBuilder<CalendarModel, EnumStatus>(this)
                    .add(EnumStatus::VALUE, &CalendarModel::value)
                    .add(EnumStatus::CONTENT, &CalendarModel::content)
                    .build();
    }; // @todo In anon namespace void initializeModel(QObject *parent)
    initializeModel(dayModel);
    initializeModel(monthModel);
    initializeModel(yearModel);
    QVector<CalendarModel> days;
    for (int i = 1; i < 32; i++) {
        days.push_back({i, QString::number(i)});
    }
    dayModel->setEntries(std::move(days));

    QVector<CalendarModel> months;
    for (int i = 0; i < 12; i++) {
        months.append({i + 1, DateStringAlternatives::monthsNames[i]});
    }

    monthModel->setEntries(std::move(months));

    QVector<CalendarModel> years;
    for (int i = minimumYear; i < maximumYear; i++) {
        years.append({i, QString::number(i)});
    }
    yearModel->setEntries(std::move(years));

    QObject::connect(this,
                     &CalendarController::currentDateChanged,
                     this,
                     &CalendarController::onCurrentDateChanged);
}

void CalendarController::setNewDate(int dayIndexDelta, int monthIndexDelta, int yearIndexDelta)
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

QString CalendarController::getNiceDateFormat() const
{
    return QString("%1 %2 %3") // @todo auto NICE_DATE_FORMAT = QStringLiteral("%1 %2 %3");
        .arg(currentDate.day())
        .arg(monthModel->data(currentDate.month() - 1, EnumStatus::CONTENT).toString())
        .arg(currentDate.year());
}
//directly from cpp
void CalendarController::changeDate(int year, int month, int day)
{
    onCurrentDateChanged(day - 1, month - 1, year - minimumYear);
    emit uploadNewDate(day - 1, month - 1, year - minimumYear);
}

void CalendarController::assignCurrent()
{
    changeDate(currentDate.year(), currentDate.month(), currentDate.day());
}

void CalendarController::clear()
{
    changeDate(minimumYear, 1, 1);
}

//directly from gui
void CalendarController::onCurrentDateChanged(int dayIndexDelta,
                                              int monthIndexDelta,
                                              int yearIndexDelta)
{
    setNewDate(dayIndexDelta, monthIndexDelta, yearIndexDelta);

    emit niceFormatChanged(getNiceDateFormat());
}

#include "calendarcontroller.h"

CalendarController::CalendarController(QObject *obj)
    : QObject(obj)
{
    auto initializeModel = [this](QPointer<CalendarListModel> &model) {
        model = FastModelBuilder<CalendarModel, EnumStatus>(this)
                    .add(EnumStatus::CONTENT, &CalendarModel::content, "content")
                    .add(EnumStatus::VALUE, &CalendarModel::value, "value")
                    .build();
    };

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
        months.append({i + 1, monthsNames[i]});
    }
    monthModel->setEntries(std::move(months));

    QVector<CalendarModel> years;
    for (int i = 1901; i < 2050; i++) {
        years.append({i, QString::number(i)});
    }
    yearModel->setEntries(std::move(years));

    QObject::connect(this,
                     &CalendarController::currentDateChanged,
                     this,
                     &CalendarController::onCurrentDateChanged);
}

QString CalendarController::getNiceDateFormat() const
{
    return QString("Birthday : %1 %2 %3")
        .arg(currentDate.day())
        .arg(monthModel->data(currentDate.month() - 1, EnumStatus::CONTENT).toString())
        .arg(currentDate.year());
}

void CalendarController::clear()
{
    emit resetGui();
    currentDate = defaultDate;
}

void CalendarController::onCurrentDateChanged(int day, int month, int year)
{
    int begin = QDate(year, month, 1).daysInMonth();
    int size = dayModel->rowCount();
    for (int i = size + 1; i <= begin; i++) {
        dayModel->addEntry({i, QString::number(i)});
    }
    int diff = size - begin;
    if (diff > 0) {
        dayModel->removeRows(begin, diff);
        day -= diff;
    }
    currentDate = QDate(year, month, day);
    emit niceFormatChanged(getNiceDateFormat());
}

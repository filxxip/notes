#include "calendarcontroller.h"

CalendarController::CalendarController(QObject *obj)
    : QObject(obj)
{
    auto initializeModel = [this](QPointer<CalendarListModel> &model) {
        model = FastModelBuilder<CalendarModel, EnumStatus>(this)
                    .add(EnumStatus::CONTENT, &CalendarModel::content, "content")
                    .add(EnumStatus::VISIBILITY, &CalendarModel::visibility, "visibility")
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

void CalendarController::onCurrentDateChanged(int day, int month, int year)
{
    qDebug() << "wchodze tututu" << day << "  " << month << "  " << year;
    int begin = QDate(year, month, 1).daysInMonth();

    int size = dayModel->rowCount();
    qDebug() << "oto size " << size;
    qDebug() << "ilosc dni : " << begin;
    for (int i = size + 1; i <= begin; i++) {
        CalendarModel c;
        c.content = QString::number(i);
        c.value = size;
        c.visibility = true;
        dayModel->addEntry(c);
    }
    int diff = size - begin;
    qDebug() << "oto diff" << diff;
    if (diff > 0) {
        qDebug() << "ilosc dni" << begin;
        dayModel->removeRows(begin, diff);
        day -= diff;
    }
    currentDate = QDate(year, month, day);
    //    while (!currentDate.isValid() && day != 0) {
    //        qDebug() << "cos ten";
    //        currentDate = QDate(year, month, --day);
    //        emit dayChanged(day);
    //    }
    //    int currentCheck = 0;
    //    while (this->dayModel->setData(currentCheck,
    //                                   QDate(year, month, currentCheck + 1).isValid(),
    //                                   EnumStatus::VISIBILITY)) {
    //        currentCheck++;
    //        qDebug() << "cos ten222";
    //    }
    emit niceFormatChanged(getNiceDateFormat());
}

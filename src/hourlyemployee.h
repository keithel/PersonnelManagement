//
//  hourlyemployee.h
//
//  Copyright (c) 2018 Keith Kyzivat
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H

#include "employee.h"

class HourlyEmployee : public Employee
{
    Q_PROPERTY(double hourlyCompensation READ hourlyCompensation WRITE setHourlyCompensation NOTIFY hourlyCompensationChanged)
    Q_PROPERTY(double doneHours READ doneHours WRITE setDoneHours NOTIFY doneHoursChanged)
    Q_OBJECT

public:
    HourlyEmployee(QObject *parent = 0);

    virtual QString type() const;

    double hourlyCompensation() const;
    void setHourlyCompensation(double hourlyCompensation);

    double doneHours() const;
    void setDoneHours(double doneHours);

    virtual double salary() const;

    virtual bool load(const QJsonObject &json);
    virtual void serialize(QJsonObject &json);

    static const QString TYPE;

signals:
    void hourlyCompensationChanged();
    void doneHoursChanged();

protected:
    double mHourlyCompensation;
    double mDoneHours;
};

#endif // HOURLYEMPLOYEE_H

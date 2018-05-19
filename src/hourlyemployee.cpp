//
//  hourlyemployee.cpp
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

#include "hourlyemployee.h"

const QString HourlyEmployee::TYPE = QString("Hourly Employee");

HourlyEmployee::HourlyEmployee(QObject *parent)
    : Employee(parent)
    , mHourlyCompensation(0)
    , mDoneHours(0)
{
}

QString HourlyEmployee::type() const
{
    return HourlyEmployee::TYPE;
}

double HourlyEmployee::hourlyCompensation() const
{
    return mHourlyCompensation;
}

void HourlyEmployee::setHourlyCompensation(double hourlyCompensation)
{
    mHourlyCompensation = hourlyCompensation;
    emit hourlyCompensationChanged();
    emit salaryChanged();
}

double HourlyEmployee::doneHours() const
{
    return mDoneHours;
}

void HourlyEmployee::setDoneHours(double doneHours)
{
    mDoneHours = doneHours;
    emit doneHoursChanged();
    emit salaryChanged();
}

double HourlyEmployee::salary() const
{
    return mDoneHours * mHourlyCompensation;
}

bool HourlyEmployee::load(const QJsonObject &json)
{
    // Have parent handle it's bit of serialization
    bool ok = Employee::load(json);

    if (json.contains("hourlyCompensation") && json["hourlyCompensation"].isDouble())
    {
        mHourlyCompensation = json["hourlyCompensation"].toDouble();
    }
    else
        ok = false;

    if (json.contains("doneHours") && json["doneHours"].isDouble())
    {
        mDoneHours = json["doneHours"].toDouble();
    }
    else
        ok = false;

    return ok;
}

void HourlyEmployee::serialize(QJsonObject &json)
{
    Employee::serialize(json);
    json["hourlyCompensation"] = mHourlyCompensation;
    json["doneHours"] = mDoneHours;
}

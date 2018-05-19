//
//  monthlyemployee.cpp
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

#include "monthlyemployee.h"

const QString MonthlyEmployee::TYPE = QString("Monthly Employee");

MonthlyEmployee::MonthlyEmployee(QObject *parent)
    : Employee(parent)
    , mMonthlyCompensation(0)
{
}

QString MonthlyEmployee::type() const
{
    return MonthlyEmployee::TYPE;
}

double MonthlyEmployee::monthlyCompensation() const
{
    return mMonthlyCompensation;
}

void MonthlyEmployee::setMonthlyCompensation(double monthlyCompensation)
{
    mMonthlyCompensation = monthlyCompensation;
    emit monthlyCompensationChanged();
    emit salaryChanged();
}

double MonthlyEmployee::salary() const
{
    return mMonthlyCompensation;
}

bool MonthlyEmployee::load(const QJsonObject &json)
{
    // Have parent handle it's bit of serialization
    bool ok = Employee::load(json);

    if (json.contains("monthlyCompensation") && json["monthlyCompensation"].isDouble())
    {
        mMonthlyCompensation = json["monthlyCompensation"].toDouble();
    }
    else
        ok = false;

    return ok;
}

void MonthlyEmployee::serialize(QJsonObject &json)
{
    Employee::serialize(json);
    json["monthlyCompensation"] = mMonthlyCompensation;
}

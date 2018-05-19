//
//  monthlyemployee.h
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

#ifndef MONTHLYEMPLOYEE_H
#define MONTHLYEMPLOYEE_H

#include "employee.h"

class MonthlyEmployee : public Employee
{
    Q_PROPERTY(double monthlyCompensation READ monthlyCompensation WRITE setMonthlyCompensation NOTIFY monthlyCompensationChanged)
    Q_OBJECT

public:
    MonthlyEmployee(QObject *parent = 0);

    virtual QString type() const;

    double monthlyCompensation() const;
    void setMonthlyCompensation(double monthlyCompensation);

    virtual double salary() const;

    virtual bool load(const QJsonObject &json);
    virtual void serialize(QJsonObject &json);

    static const QString TYPE;

signals:
    void monthlyCompensationChanged();

protected:
    double mMonthlyCompensation;
};

#endif // MONTHLYEMPLOYEE_H

//
//  employee.cpp
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

#include "employee.h"

const QString Employee::TYPE = QString("Employee");

Employee::Employee(QObject *parent)
    : QObject(parent)
{
}

QString Employee::type() const
{
    return Employee::TYPE;
}

QString Employee::name() const
{
    return mName;
}

void Employee::setName(const QString& name)
{
    mName = name;
    emit nameChanged();
}

QString Employee::ssn() const
{
    return mSsn;
}

void Employee::setSsn(const QString& ssn)
{
    mSsn = ssn;
    emit ssnChanged();
}

bool Employee::load(const QJsonObject &json)
{
    bool ok = true;
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
    else
        ok = false;

    if (json.contains("ssn") && json["ssn"].isString())
    {
        mSsn = json["ssn"].toString();
    }
    else
        ok = false;

    return ok;
}

void Employee::serialize(QJsonObject &json)
{
    json["name"] = mName;
    json["ssn"] = mSsn;
}

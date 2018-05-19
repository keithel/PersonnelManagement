//
//  salesemployee.cpp
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

#include "salesemployee.h"

const QString SalesEmployee::TYPE = QString("Sales Employee");

SalesEmployee::SalesEmployee(QObject *parent)
    : MonthlyEmployee(parent)
    , mBonusPercent(0)
    , mRealizedOutcome(0)
    , mOutcomeClaim(0)
{

}

QString SalesEmployee::type() const
{
    return SalesEmployee::TYPE;
}

double SalesEmployee::bonusPercent() const
{
    return mBonusPercent;
}

void SalesEmployee::setBonusPercent(double bonusPercent)
{
    mBonusPercent = bonusPercent;
    emit bonusPercentChanged();
}

double SalesEmployee::realizedOutcome() const
{
    return mRealizedOutcome;
}

void SalesEmployee::setRealizedOutcome(double realizedOutcome)
{
    mRealizedOutcome = realizedOutcome;
    emit realizedOutcomeChanged();
    emit salaryChanged();
}

double SalesEmployee::outcomeClaim() const
{
    return mOutcomeClaim;
}

void SalesEmployee::setOutcomeClaim(double outcomeClaim)
{
    mOutcomeClaim = outcomeClaim;
    emit outcomeClaimChanged();
    emit salaryChanged();
}

double SalesEmployee::salary() const
{
    double bonusPercent = (mRealizedOutcome >= mOutcomeClaim) ? mBonusPercent : 0;
    return mMonthlyCompensation + mMonthlyCompensation*(bonusPercent/100);
}

bool SalesEmployee::load(const QJsonObject &json)
{
    // Have parent handle it's bit of serialization
    bool ok = MonthlyEmployee::load(json);

    if (json.contains("bonusPercent") && json["bonusPercent"].isDouble())
    {
        mBonusPercent = json["bonusPercent"].toDouble();
    }
    else
        ok = false;

    if (json.contains("realizedOutcome") && json["realizedOutcome"].isDouble())
    {
        mRealizedOutcome = json["realizedOutcome"].toDouble();
    }
    else
        ok = false;

    if (json.contains("outcomeClaim") && json["outcomeClaim"].isDouble())
    {
        mOutcomeClaim = json["outcomeClaim"].toDouble();
    }
    else
        ok = false;

    return ok;
}

void SalesEmployee::serialize(QJsonObject &json)
{
    MonthlyEmployee::serialize(json);
    json["bonusPercent"] = mBonusPercent;
    json["outcomeClaim"] = mOutcomeClaim;
    json["realizedOutcome"] = mRealizedOutcome;
}

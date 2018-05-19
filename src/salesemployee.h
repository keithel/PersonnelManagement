//
//  salesemployee.h
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

#ifndef SALESEMPLOYEE_H
#define SALESEMPLOYEE_H

#include "monthlyemployee.h"

class SalesEmployee : public MonthlyEmployee
{
    Q_PROPERTY(double bonusPercent READ bonusPercent WRITE setBonusPercent NOTIFY bonusPercentChanged)
    Q_PROPERTY(double realizedOutcome READ realizedOutcome WRITE setRealizedOutcome NOTIFY realizedOutcomeChanged)
    Q_PROPERTY(double outcomeClaim READ outcomeClaim WRITE setOutcomeClaim NOTIFY outcomeClaimChanged)
    Q_OBJECT

public:
    SalesEmployee(QObject *parent = 0);

    virtual QString type() const;

    double bonusPercent() const;
    void setBonusPercent(double bonusPercent);

    double realizedOutcome() const;
    void setRealizedOutcome(double realizedOutcome);

    double outcomeClaim() const;
    void setOutcomeClaim(double outcomeClaim);

    virtual double salary() const;

    virtual bool load(const QJsonObject &json);
    virtual void serialize(QJsonObject &json);

    static const QString TYPE;

signals:
    void bonusPercentChanged();
    void realizedOutcomeChanged();
    void outcomeClaimChanged();

protected:
    double mBonusPercent;
    double mRealizedOutcome;
    double mOutcomeClaim;
};

#endif // SALESEMPLOYEE_H

//
//  employee.h
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

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class Employee : public QObject
{
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString ssn READ ssn WRITE setSsn NOTIFY ssnChanged)
    Q_PROPERTY(double salary READ salary NOTIFY salaryChanged)
    Q_PROPERTY(QString type READ type)
    Q_OBJECT

public:
    virtual QString type() const;

    QString name() const;
    void setName(const QString& name);

    QString ssn() const;
    void setSsn(const QString& ssn);

    virtual double salary() const = 0;

    virtual bool load(const QJsonObject &json);
    virtual void serialize(QJsonObject &json);

    static const QString TYPE;

signals:
    void nameChanged();
    void ssnChanged();
    void salaryChanged();

protected:
    explicit Employee(QObject *parent = 0);

    QString mName;
    QString mSsn;
};

#endif // EMPLOYEE_H

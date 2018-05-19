//
//  employeemodel.cpp
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

#include "employeemodel.h"
#include "employee.h"
#include "monthlyemployee.h"
#include "hourlyemployee.h"
#include "salesemployee.h"
#include <QLocale>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent)
    , mLastSaveOk(true)
{
    mSaveFile = new QFile("personnelManagement.json", this);
}

EmployeeModel::~EmployeeModel()
{}

QStringList EmployeeModel::employeeTypes()
{
    return QStringList({
        MonthlyEmployee::TYPE,
        HourlyEmployee::TYPE,
        SalesEmployee::TYPE
    });
}

bool EmployeeModel::lastSaveOk()
{
    return mLastSaveOk;
}

int EmployeeModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return mEmployees.size();
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const
{
    // return an empty value for invalid indexes.
    if (!index.isValid() || index.row() < 0 || index.row() >= mEmployees.size())
        return QVariant();

    // If the employee pointer at the index happens to be null, just return an empty value.
    Employee* employee = mEmployees.at(index.row());
    if (employee == nullptr)
        return QVariant();

    // If the employee at the index is one of the derived types, set up variables to access them.
    MonthlyEmployee* monthlyEmployee = employee->inherits(MonthlyEmployee::staticMetaObject.className()) ? (MonthlyEmployee*) employee : nullptr;
    HourlyEmployee* hourlyEmployee = employee->inherits(HourlyEmployee::staticMetaObject.className()) ? (HourlyEmployee*) employee : nullptr;
    SalesEmployee* salesEmployee = employee->inherits(SalesEmployee::staticMetaObject.className()) ? (SalesEmployee*) employee : nullptr;

    QVariant retVal;
    switch (role)
    {
    case EmployeeTypeRole:
        retVal.setValue(employee->type());
        break;
    case NameRole:
        retVal.setValue(employee->name());
        break;
    case SsnRole:
        retVal.setValue(employee->ssn());
        break;
    case SalaryRole:
        retVal.setValue(employee->salary());
        break;
    case MonthlyCompensationRole:
        if (monthlyEmployee != nullptr)
            retVal.setValue(monthlyEmployee->monthlyCompensation());
        break;
    case HourlyCompensationRole:
        if (hourlyEmployee != nullptr)
            retVal.setValue(hourlyEmployee->hourlyCompensation());
        break;
    case DoneHoursRole:
        if (hourlyEmployee != nullptr)
            retVal.setValue(hourlyEmployee->doneHours());
        break;
    case BonusPercentRole:
        if (salesEmployee != nullptr)
            retVal.setValue(salesEmployee->bonusPercent());
        break;
    case RealizedOutcomeRole:
        if (salesEmployee != nullptr)
            retVal.setValue(salesEmployee->realizedOutcome());
        break;
    case OutcomeClaimRole:
        if (salesEmployee != nullptr)
            retVal.setValue(salesEmployee->outcomeClaim());
        break;
    }

    return retVal;
}

bool EmployeeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Employee* employee = mEmployees.at(index.row());
        if (employee == nullptr)
            return false;

        // If the employee at the index is one of the derived types, set up variables to access them.
        MonthlyEmployee* monthlyEmployee = employee->inherits(MonthlyEmployee::staticMetaObject.className()) ? (MonthlyEmployee*) employee : nullptr;
        HourlyEmployee* hourlyEmployee = employee->inherits(HourlyEmployee::staticMetaObject.className()) ? (HourlyEmployee*) employee : nullptr;
        SalesEmployee* salesEmployee = employee->inherits(SalesEmployee::staticMetaObject.className()) ? (SalesEmployee*) employee : nullptr;

        bool doubleOk = false;
        QVector<int> rolesChanged;

        switch (role)
        {
        case EmployeeTypeRole:
            return false;  // Can't change type - this is a read-only role.
        case NameRole:
            employee->setName(value.toString());
            break;
        case SsnRole:
            employee->setSsn(value.toString());
            break;
        case SalaryRole:
            return false; // Can't change salary directly - this is a read-only role.
        case MonthlyCompensationRole:
            if (monthlyEmployee != nullptr)
            {
                double dblVal = currencyVariantToDouble(value, doubleOk);
                // Don't set the value if the double conversion fails - we'll silently ignore the set value.
                if (!doubleOk)
                    return false;
                monthlyEmployee->setMonthlyCompensation(dblVal);
                rolesChanged << SalaryRole;
            }
            break;
        case HourlyCompensationRole:
            if (hourlyEmployee != nullptr)
            {
                double dblVal = currencyVariantToDouble(value, doubleOk);
                if (!doubleOk)
                    return false;
                hourlyEmployee->setHourlyCompensation(dblVal);
                rolesChanged << SalaryRole;
            }
            break;
        case DoneHoursRole:
            if (hourlyEmployee != nullptr)
            {
                double dblVal = value.toDouble(&doubleOk);
                if (!doubleOk)
                    return false;
                hourlyEmployee->setDoneHours(dblVal);
                rolesChanged << SalaryRole;
            }
            break;
        case BonusPercentRole:
            if (salesEmployee != nullptr)
            {
                double dblVal = percentVariantToDouble(value, doubleOk);
                if (!doubleOk)
                    return false;
                salesEmployee->setBonusPercent(dblVal);
                rolesChanged << SalaryRole;
            }
            break;
        case RealizedOutcomeRole:
            if (salesEmployee != nullptr)
            {
                double dblVal = currencyVariantToDouble(value, doubleOk);
                if (!doubleOk)
                    return false;
                salesEmployee->setRealizedOutcome(dblVal);
                rolesChanged << SalaryRole;
            }
            break;
        case OutcomeClaimRole:
            if (salesEmployee != nullptr)
            {
                double dblVal = currencyVariantToDouble(value, doubleOk);
                if (!doubleOk)
                    return false;
                salesEmployee->setOutcomeClaim(dblVal);
                rolesChanged << SalaryRole;
            }
            break;
        }

        emit dataChanged(index, index, rolesChanged << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EmployeeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> EmployeeModel::roleNames() const
{
    QHash<int, QByteArray> roles = {
        { EmployeeTypeRole, "type" },
        { NameRole, "name" },
        { SsnRole, "ssn"},
        { SalaryRole, "salary"},
        { MonthlyCompensationRole, "monthlyCompensation" },
        { HourlyCompensationRole, "hourlyCompensation" },
        { DoneHoursRole, "doneHours" },
        { BonusPercentRole, "bonusPercent" },
        { RealizedOutcomeRole, "realizedOutcome" },
        { OutcomeClaimRole, "outcomeClaim" }
    };

    return roles;
}

void EmployeeModel::addEmployee(const QString& employeeType)
{
    const int index = mEmployees.size();
    beginInsertRows(QModelIndex(), index, index);

    Employee* employee = nullptr;

    if (employeeType == MonthlyEmployee::TYPE)
        employee = new MonthlyEmployee(this);
    else if (employeeType == HourlyEmployee::TYPE)
        employee = new HourlyEmployee(this);
    else if (employeeType == SalesEmployee::TYPE)
        employee = new SalesEmployee(this);

    mEmployees.append(employee);

    endInsertRows();
}

void EmployeeModel::removeEmployee(int index)
{
    beginRemoveRows(QModelIndex(), index, index);

    mEmployees.removeAt(index);

    endRemoveRows();
}

bool EmployeeModel::load()
{
    QFile saveFile(mSaveFile->fileName());
    if (!saveFile.open(QIODevice::ReadOnly))
    {
        qWarning("Faled to open the employee save file for loading.");
        return false;
    }

    QByteArray employeeData = saveFile.readAll();

    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(employeeData, &jsonParseError);

    if (jsonParseError.error != QJsonParseError::NoError)
    {
        qWarning("Failed to load saved employees - %s", qPrintable(jsonParseError.errorString()));
        return false;
    }

    QJsonObject rootObject = doc.object();
    if (!(rootObject.contains("employees") && rootObject["employees"].isArray()))
    {
        qWarning("Failed to load saved employees - %s", "no 'employees' base json array");
        return false;
    }

    QVector<Employee*> newEmployees;
    QJsonArray employeesJson = rootObject["employees"].toArray();
    for(QJsonValue employeeJsonValue : employeesJson)
    {
        QJsonObject employeeJson = employeeJsonValue.toObject();
        if (!(employeeJson.contains("type") && employeeJson["type"].isString()))
        {
            qWarning("Failed to load saved employees - %s", "employee without a type");
            return false;
        }

        Employee* newEmployee = nullptr;
        QString employeeType = employeeJson["type"].toString();
        if (employeeType == MonthlyEmployee::TYPE)
        {
            newEmployee = new MonthlyEmployee(this);
        }
        else if (employeeType == HourlyEmployee::TYPE)
        {
            newEmployee = new HourlyEmployee(this);
        }
        else if (employeeType == SalesEmployee::TYPE)
        {
            newEmployee = new SalesEmployee(this);
        }

        if (!newEmployee->load(employeeJson))
        {
            qWarning("Failed to load saved employee, employee specific json load failure.");
            return false;
        }
        newEmployees.append(newEmployee);
    }

    beginResetModel();
    mEmployees = newEmployees;
    endResetModel();

    return true;
}

bool EmployeeModel::save()
{
    QJsonObject employeesJson;
    QJsonArray employeeArray;
    for (Employee* employee : mEmployees)
    {
        QJsonObject json;
        json["type"] = employee->type();
        employee->serialize(json);
        employeeArray.append(json);
    }
    employeesJson["employees"] = employeeArray;

    // Rename the existing save file with .bak extension,
    // removing any older backup.
    if (mSaveFile->exists())
    {
        QString backupExt = ".bak";
        QFile(mSaveFile->fileName() + backupExt).remove();
        QFile(mSaveFile->fileName()).rename(mSaveFile->fileName() + backupExt);
    }

    QJsonDocument jsonDocument(employeesJson);
    if (!mSaveFile->open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file for writing.");
        if (mLastSaveOk != false)
        {
            mLastSaveOk = false;
            emit lastSaveOkChanged();
        }
        return false;
    }

    // Try to write the file.
    QByteArray jsonBytes = jsonDocument.toJson();
    qint64 bytesWritten = mSaveFile->write(jsonBytes);
    bool ok = bytesWritten >= 0;

    // Emit signal if there's a change in failure/ok for save operation.
    if (mLastSaveOk != ok)
    {
        mLastSaveOk = ok;
        emit lastSaveOkChanged();
    }

    mSaveFile->close();

    return ok;
}

double EmployeeModel::currencyVariantToDouble(const QVariant &value, bool &doubleOk)
{
    QString str = value.toString();
    if (str.length() <= 0)
    {
        doubleOk = false;
        return -1;
    }

    QLocale locale;
    str = str.remove(locale.currencySymbol());

    return locale.toDouble(str, &doubleOk);
}

double EmployeeModel::percentVariantToDouble(const QVariant &value, bool &doubleOk)
{
    QString str = value.toString();
    if (str.length() <= 0)
    {
        doubleOk = false;
        return -1;
    }

    QLocale locale;
    str = str.remove(locale.percent());

    return locale.toDouble(str, &doubleOk);
}

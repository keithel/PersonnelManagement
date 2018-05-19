//
//  employeemodel.h
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

#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QAbstractListModel>
#include <QFile>

class Employee;

class EmployeeModel : public QAbstractListModel
{
    Q_PROPERTY(QStringList employeeTypes READ employeeTypes NOTIFY employeeTypesChanged)
    Q_PROPERTY(bool lastSaveOk READ lastSaveOk NOTIFY lastSaveOkChanged)
    Q_OBJECT

public:
    explicit EmployeeModel(QObject *parent = nullptr);
    virtual ~EmployeeModel();

    enum Roles {
        EmployeeTypeRole = Qt::UserRole,
        NameRole,
        SsnRole,
        SalaryRole,
        MonthlyCompensationRole,
        HourlyCompensationRole,
        DoneHoursRole,
        BonusPercentRole,
        RealizedOutcomeRole,
        OutcomeClaimRole
    };

    QStringList employeeTypes();
    bool lastSaveOk();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

signals:
    void employeeTypesChanged(); // This signal is unused, but shuts up the QML engine - we don't need notify since this will never change.
    void lastSaveOkChanged();

public slots:
    void addEmployee(const QString& employeeType);
    void removeEmployee(int index);
    bool load();
    bool save();

private:
    double currencyVariantToDouble(const QVariant& value, bool& doubleOk);
    double percentVariantToDouble(const QVariant& value, bool& doubleOk);

    QVector<Employee*> mEmployees;
    QFile* mSaveFile;
    bool mLastSaveOk;

};

#endif // EMPLOYEEMODEL_H

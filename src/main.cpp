//
//  main.cpp
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

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "employeemodel.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    qmlRegisterType<EmployeeModel>("name.kyzivat.PersonnelManagement", 1, 0, "EmployeeModel");

    QQmlApplicationEngine engine;

    // Since I only want to enforce one instance of EmployeeModel due to saving/loading,
    // I'm opting to use setContextProperty over registering EmployeeModel as an QML accessible type.
    EmployeeModel employeeModel(&engine);
    employeeModel.load();

    engine.rootContext()->setContextProperty(QStringLiteral("employeeModel"), &employeeModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

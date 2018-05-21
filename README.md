#Personnel Management
* * *

A Simple Personnel Management applicaton demo written in Qt/QML.

This is a cross-platform application that will work for Linux, Mac and Windows.
It should also work with Android and iOS, however it may need some cosmetic changes to make it look good there.
This is written with and requires the Qt toolkit.

## Features

* Employees stored in one of 3 different derived Employee classes
  based on their type - MonthlyEmployee, HourlyEmployee, or SalaryEmployee
  (this shows polymorphism)
* There is a simple user interface that shows each employee in a QML listview
  presented from C++ QAbstractListModel derived model.
* Users can be added and removed.
* Salary is calculated differently per Employee type, performed in the
  salary method of each Employee type.
* Employees can be saved. The next time the application launches,
  previously saved employees are loaded back into the app.

## Requires

* Qt rev 5.8+
* Qt Creator (v4.6.1 tested)

Build
=====
* Install Qt 5.8+ and Qt Creator (http://www.qt.io/)
* Open the PersonnelManagement.pro file
* Click "Run", and the app should run.

Copyright
=========
This software Copyright 2018 Keith Kyzivat

License
=======

This project is licensed under the [Gnu Lesser General Public License, Version 3] (https://choosealicense.com/licenses/gpl-3.0/).


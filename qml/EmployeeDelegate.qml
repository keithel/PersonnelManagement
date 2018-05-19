//
//  EmployeeDelegate.qml
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

import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Frame {
    id: topLevel

    property var currencyRe: new RegExp("^\\" + locale.currencySymbol() + "?([1-9]{1}[0-9]{0,2}(\\"
                                        + locale.groupSeparator + "\\d{3})*(\\"
                                        + locale.decimalPoint + "\\d{0,2})?|[1-9]{1}\\d{0,}(\\"
                                        + locale.decimalPoint + "\\d{0,2})?|0(\\"
                                        + locale.decimalPoint + "\\d{0,2})?|(\\"
                                        + locale.decimalPoint + "\\d{1,2}))$")
    signal remove(int idx);

    GridLayout {
        id: gridLayout
        // This US currency regular expression comes from https://stackoverflow.com/a/354276
        anchors.fill: parent

        columns: 2
        Text {
            font.bold: true
            Layout.fillWidth: true
            text: model.type;
        }
        Button {
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 5
            Layout.columnSpan: gridLayout.columns-1
            background: Item {}
            Image {
                anchors.centerIn: parent
                source: "qrc:///cancel24.png"
            }
            onClicked: topLevel.remove(index);
        }

        LabeledTextField {
            Layout.fillWidth: true
            labelText: "Full Name"
            placeholderText: "Full Name"
            text: model.name
            onEditingFinished: model.name = text
        }
        LabeledTextField {
            Layout.fillWidth: true
            labelText: "Social Security Number"
            placeholderText: "000-00-0000"
            inputMask: "999-99-9999"
            text: model.ssn
            onEditingFinished: model.ssn = text
        }

        LabeledTextField {
            Layout.fillWidth: true
            visible: model.type === "Hourly Employee"
            labelText: "Hourly Compensation"
            placeholderText: locale.currencySymbol() + "15" + locale.decimalPoint + "00"
            validator: RegExpValidator { regExp: currencyRe }
            text: visible ? Number(model.hourlyCompensation).toLocaleCurrencyString(locale) : -1
            onEditingFinished: model.hourlyCompensation = text
        }
        LabeledTextField {
            Layout.fillWidth: true
            visible: model.type === "Hourly Employee"
            labelText: "Done Hours"
            placeholderText: "40"
            inputMask: "09" + locale.decimalPoint + "00"
            text: visible ? Number(model.doneHours).toFixed(5).toLocaleString() : -1
            onEditingFinished: model.doneHours = text;
        }

        LabeledTextField {
            Layout.fillWidth: true
            visible: (model.type === "Monthly Employee" || model.type === "Sales Employee")
            labelText: "Monthly Compensation"
            placeholderText: locale.currencySymbol() + "4" + locale.groupSeparator + "000" + locale.decimalPoint + "00"
            validator: RegExpValidator { regExp: currencyRe }
            text: visible ? Number(model.monthlyCompensation).toLocaleCurrencyString(locale) : -1
            onEditingFinished: model.monthlyCompensation = text;
        }

        LabeledTextField {
            Layout.fillWidth: true
            visible: model.type === "Sales Employee"
            labelText: "Bonus Percent"
            placeholderText: "10" + locale.decimalPoint + "00%"
            inputMask: "09" + locale.decimalPoint + "00" + locale.percent
            text: visible ? Number(model.bonusPercent).toFixed(4).toLocaleString() + "%" : -1
            onEditingFinished: model.bonusPercent = text;
        }
        LabeledTextField {
            Layout.fillWidth: true
            visible: model.type === "Sales Employee"
            labelText: "Realized Outcome"
            placeholderText: locale.currencySymbol() + "150" + locale.groupSeparator + "000"
            validator: RegExpValidator { regExp: currencyRe }
            text: visible ? Number(model.realizedOutcome).toLocaleCurrencyString(locale) : -1
            onEditingFinished: model.realizedOutcome = text;
        }
        LabeledTextField {
            Layout.fillWidth: true
            visible: model.type === "Sales Employee"
            labelText: "Outcome Claim"
            placeholderText: locale.currencySymbol() + "150" + locale.groupSeparator + "000"
            validator: RegExpValidator { regExp: currencyRe }
            text: visible ? Number(model.outcomeClaim).toLocaleCurrencyString(locale) : -1
            onEditingFinished: model.outcomeClaim = text;
        }

        LabeledTextField {
            Layout.fillWidth: true
            Layout.columnSpan: gridLayout.columns
            labelText: "Salary"
            bold: true
            placeholderText: locale.currencySymbol() + "3" + locale.groupSeparator + "000"
            validator: RegExpValidator { regExp: currencyRe }
            readOnly: true
            text: Number(model.salary).toLocaleCurrencyString(locale);
        }

    }
}

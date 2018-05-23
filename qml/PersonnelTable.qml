//
//  PersonnelTable.qml
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


// NOTE: This affected by bug: https://bugreports.qt.io/browse/QTBUG-59796
//       If you see swipeview broken by scrolling the listview, you have
//       encountered this bug.
Page {
    ListView {
        id: listView
        anchors.fill: parent

        contentWidth: headerItem.width

        header: Row {
            spacing: 1
            function itemAt(index) { return repeater.itemAt(index) }
            Repeater {
                id: repeater
                model: ["Type", "Name", "SSN", "Salary"]
                Label {
                    text: modelData
                    font.bold: true
                    font.pixelSize: 20
                    padding: 10
                    background: Rectangle { color: "silver" }
                    width: listView.width/4
                }
            }
        }

        model: employeeModel
        delegate: Column {
            id: delegate
            property int row: index
            Row {
                spacing: 1
                ItemDelegate {
                    text: model.type
                    width: listView.headerItem.itemAt(0).width
                }
                ItemDelegate {
                    text: model.name
                    width: listView.headerItem.itemAt(1).width
                }
                ItemDelegate {
                    text: model.ssn
                    width: listView.headerItem.itemAt(2).width
                }
                ItemDelegate {
                    text: Number(model.salary).toLocaleCurrencyString(locale);
                    width: listView.headerItem.itemAt(3).width
                }
            }
            Rectangle {
                color: "silver"
                width: parent.width
                height: 1
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }
}

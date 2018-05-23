//
//  PersonnelEntryList.qml
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
//import name.kyzivat.PersonnelManagement 1.0;

Page {

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        RowLayout {
            ComboBox {
                implicitWidth: 190 // On > Qt 5.8.0, the implicit width is not as wide as the largest model item :(
                id: typeCombo
                model: listView.model.employeeTypes
            }

            Button {
                id: addEmployeeButton
                Layout.fillWidth: true
                text: qsTr("Add Employee");
                onClicked: listView.model.addEmployee(typeCombo.currentText);
            }

            Button {
                Layout.fillWidth: true
                implicitWidth: addEmployeeButton.implicitWidth
                text: qsTr("Save")
                onClicked: listView.model.save();
                hoverEnabled: true

                ToolTip.delay: 1000
                ToolTip.timeout: 5000
                ToolTip.visible: !listView.model.lastSaveOk && hovered;
                ToolTip.text: listView.model.lastSaveOk ? "Save the document" : qsTr("Last save failed");

                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    opacity: enabled ? 1.0 : 0.3
                    color: listView.model.lastSaveOk ? "#000000" : "red"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
            }
        }

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: listView

                implicitWidth: 500
                implicitHeight: 300
                anchors.fill: parent
                clip: true

                model: employeeModel

                delegate: EmployeeDelegate {
                    width: parent.width
                    onRemove: listView.model.removeEmployee(idx)
                }
            }
        }

    }
}

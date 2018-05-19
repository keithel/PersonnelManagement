//
//  LabeledTextField.qml
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

import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

ColumnLayout {
    id: topLevel
    property alias labelText: label.text
    property bool bold: false
    property alias placeholderText: textField.placeholderText
    property alias text: textField.text
    property alias inputMask: textField.inputMask
    property alias validator: textField.validator
    property alias readOnly: textField.readOnly
    signal editingFinished(string text)

    spacing: -7

    TextField {
        id: textField
        Layout.fillWidth: true
        font.bold: topLevel.bold
        onEditingFinished: topLevel.editingFinished(text)
    }
    Label {
        id: label
        font.pixelSize: 10
        font.bold: topLevel.bold
        Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
    }
}

//
//  main.qml
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

ApplicationWindow {
    visible: true
    width: 1280
    height: 600
    title: qsTr("Hello World")
    id: root

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        // An editable list of employees
        PersonnelEntryList {
        }

        PersonnelTable {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Personnel Entry")
        }
        TabButton {
            text: qsTr("Personnel Table")
        }
    }

}

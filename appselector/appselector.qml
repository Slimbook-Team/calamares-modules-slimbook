/* === This file is part of calamares-modules-slimbook - <https://github.com/Slimbook-Team> ===
 *
 *   SPDX-FileCopyrightText: 2024 Slimbook <dev@slimbook.es>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
  */

import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.6 as QQC2

QQC2.Page {
    anchors.fill: parent

    ColumnLayout {
        spacing: 12
        anchors.fill: parent
        QQC2.Label {
            id: lblTitle
            Layout.fillWidth: true
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            text: (config.name == "Unknown") ? qsTr("Slimbook Apps") : qsTr("Slimbook Apps for ") + config.name
        }

        QQC2.Label {
            id: lblHelp
            Layout.fillWidth: true
            text: qsTr("Select extra packages to install")
            font.pointSize: 12
        }

        ListView {
            id: layoutsView
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 6

            model: config.appsModel

            focus: true

            QQC2.ScrollBar.vertical: QQC2.ScrollBar {}

            delegate:

                RowLayout {
                    spacing: 4

                    QQC2.CheckBox {
                        checked: modelData.checked
                        enabled: !modelData.core

                        onToggled: {

                            modelData.checked=checked;
                        }
                    }
                    QQC2.Label {
                        text: modelData.description
                    }
                }

            }

            QQC2.Label {
                id: lblDevice
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignLeft
                text: qsTr("Device: ") + config.product
                font.pointSize: 8
            }
    }
}

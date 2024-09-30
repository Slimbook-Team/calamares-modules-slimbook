import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.6 as QQC2
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kirigami 2.5 as Kirigami

QQC2.Page {
    anchors.fill: parent

    ColumnLayout {
        spacing: Kirigami.Units.largeSpacing*4
        anchors.fill: parent
        QQC2.Label {
            id: lblTitle
            Layout.fillWidth: true
            text: "Slimbook Apps for " + config.name
        }

        QQC2.Label {
            id: lblDevice
            Layout.fillWidth: true
            text: "Device:" + config.product
        }

        ListView {
            id: layoutsView
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: Kirigami.Units.largeSpacing*2

            model: config.appsModel

            focus: true

            QQC2.ScrollBar.vertical: QQC2.ScrollBar {}

            delegate:

                RowLayout {
                    spacing: Kirigami.Units.smallSpacing

                    QQC2.CheckBox {
                        /*
                        icon.name: modelData.iconName
                        icon.width: 32
                        icon.height: 32
                        */
                        checked: modelData.checked
                        enabled: modelData.core

                        onToggled: {

                            modelData.checked=checked;
                        }
                    }
                    QQC2.Label {
                        text: modelData.description
                    }
                }

            }
    }
}

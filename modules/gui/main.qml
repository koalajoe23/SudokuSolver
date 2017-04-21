import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import SudokuSolver 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("SudokuSolver")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("About")
                onTriggered: aboutDialog.visible = true
            }
        }
    }

    color: "grey"

    Dialog {
        id: aboutDialog
        title: qsTr("About")
        standardButtons: StandardButton.Close

        AboutDialog {}
    }

    Board {
        id: board
        model: BoardModel {

        }

        anchors.fill: parent
    }
}

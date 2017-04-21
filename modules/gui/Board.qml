import QtQuick 2.6
import SudokuSolver 1.0

Item {
    id: root

    property BoardModel model

    QtObject {
        id: d
        property real size: Math.min(root.height, root.width)
    }
    anchors.fill: parent

    Rectangle {
        anchors.centerIn: parent

        height: d.size
        width: d.size
        color: "black"

        Grid {
            columns: root.model.size
            rows: root.model.size

            Repeater {
                model: root.model

                Rectangle {
                    height: parent.height / 9
                    width: parent.width / 9
                    color: "green"
                }
            }
        }
    }
}

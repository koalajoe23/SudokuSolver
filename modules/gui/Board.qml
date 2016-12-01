import QtQuick 2.6

Item {
    id: root

    QtObject {
        id: d
        property real size: Math.min(root.height, root.width)
        property color backgroundColor: "white"
        property int outerBorderSize: 3
        property color outerBorderColor: "black"
    }
    anchors.fill: parent

    Rectangle {
        anchors.centerIn: parent
        border {
            color: d.outerBorderColor
            width: d.outerBorderSize
        }

        height: d.size
        width: d.size
        color: d.backgroundColor
    }

    /*Cell {
        anchors.fill: parent
    }*/
}

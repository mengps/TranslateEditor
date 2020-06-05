import QtQuick 2.13

Rectangle {
    id: root
    width: 18
    height: width
    radius: width / 2
    border.color: hovered ? darkerColor : borderColor

    property bool hovered: false
    property color borderColor: "gray"
    property color darkerColor: Qt.darker(borderColor, 1.8)

    Rectangle {
        id: ring
        anchors.centerIn: parent
        color: root.hovered ? darkerColor : borderColor
        width: 10
        height: width
        radius: width / 2
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: parent.hovered = true;
        onExited: parent.hovered = false;
    }
}

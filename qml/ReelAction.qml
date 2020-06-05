import QtQuick 2.13

Rectangle {
    id: root
    objectName: "ReelAction"
    width: parent.width
    height: 40

    property bool hovered: false
    property alias text: txt.text
    property alias textColor: txt.color
    property alias font: txt.font

    /**
     * 大部分情况下都不要动
     */
    property alias __mouseArea: mouseArea

    signal clicked();
    signal pressed();
    signal released();

    Text {
        id: txt
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        id: mouseArea
        x: root.x
        y: root.y
        width: root.width
        height: root.height
        hoverEnabled: true
        onEntered: root.hovered = true;
        onExited: root.hovered = false;
        onPressed: root.pressed();
        onReleased: root.released();
        onClicked: root.clicked();
    }
}

import QtQuick 2.13

Rectangle {
    id: root
    clip: true
    width: menuWidth
    height: menuHeight
    color: hovered ? expandColor : reduceColor

    property bool hovered: false
    property real menuWidth: 80
    property real menuHeight: 36
    property real expandHeight: menuHeight
    property color expandColor: "#FF9968"
    property color reduceColor: "#FF9968"

    property alias text: txt.text
    property alias textColor: txt.color
    property alias font: txt.font

    /**
     * 只有通过这种方式，才可以直接插入
     * 类似： ReelAction { }
     * @warning 必须提供MouseArea，否则无法触发Mouse Event
     */
    Component.onCompleted: {
        for (let i = 2; i < children.length; i++) {
            let item = children[i];
            let prevItem = children[i - 1];
            item.y = prevItem.y + prevItem.height;
            expandHeight += item.height;
            if (item.objectName === "ReelAction")
                item.__mouseArea.parent = mouseArea;
        }
    }

    MouseArea {
        id: mouseArea
        y: 0
        width: parent.width
        height: parent.height
        hoverEnabled: true
        onEntered: {
            root.hovered = true;
            expandAnimation.restart();
        }
        onExited: {
            root.hovered = false;
            reduceAnimation.restart();
        }
    }

    Text {
        id: txt
        width: parent.menuWidth
        height: parent.menuHeight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    NumberAnimation on height {
        id: expandAnimation
        duration: 220
        to: expandHeight
    }

    NumberAnimation on height {
        id: reduceAnimation
        duration: 220
        to: menuHeight
    }
}

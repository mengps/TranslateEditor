import QtQuick 2.13

Rectangle {
    id: root
    color: hovered ? "#9AFFFFFF" : "transparent"

    property string normalImage: "qrc:/image/close_normal.png"
    property string pressedImage: "qrc:/image/close_down.png"
    property string hoveredImage: "qrc:/image/close_hover.png"
    property bool hovered: false

    signal pressed();
    signal released();
    signal clicked();
    signal exited();
    signal entered();

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        antialiasing: true
        mipmap: true
        source: root.normalImage
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.entered();
            root.hovered = true;
            image.source = root.hoveredImage;
        }
        onExited: {
            root.exited();
            root.hovered = false;
            image.source = root.normalImage;
        }
        onClicked: root.clicked();
        onPressed: {
            root.pressed();
            image.source = root.pressedImage;
        }
        onReleased: {
            root.released();
            image.source = root.normalImage;
        }
    }
}

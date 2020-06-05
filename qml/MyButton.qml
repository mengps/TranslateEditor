import QtQuick 2.13
import QtQuick 2.12

Rectangle {
    id: root
    color: hovered ? "#9AFFFFFF" : "transparent"

    property string normalImage: ""
    property string pressedImage: ""
    property string hoveredImage: ""
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

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                root.entered();
                root.hovered = true;
                image.source = hoveredImage;
            }
            onClicked: root.clicked();
            onPressed: {
                root.pressed();
                image.source = pressedImage;
            }
            onReleased: {
                root.released();
                image.source = normalImage;
            }
            onExited: {
                root.exited();
                root.hovered = false;
                image.source = normalImage;
            }
        }
    }
}

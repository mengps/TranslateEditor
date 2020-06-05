import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import an.window 1.0
import an.document 1.0

FramelessWindow {
    id: root
    visible: false

    property var fileNames: []
    property var lines: []

    function fadeIn() {
        root.visible = true;
        root.raise();
        animation.restart();
    }
    function loadCode(code) { codeView.text = code; }

    Component.onCompleted: animation.restart();

    NumberAnimation {
        id: animation
        target: root
        property: "opacity"
        from: 0
        to: 1
        duration: 300
        onStopped: {
            /**
             * 高亮所有Translate Source Text
             * 移动视图到第一个高亮行
             */
            codeView.text = fileApi.openFile(fileNames[0]);
            for (let i = 0; i < root.lines.length; i++)
                docHelper.highlightLine(lines[i]);
            let pos = (root.lines[0] - 15);
            scrollBar.position = pos < 0 ? 0 : pos / codeView.lineCount;
        }
    }

    Rectangle {
        id: codeBlock
        anchors.fill: parent
        color: "transparent"
        radius: 6

        Image {
            anchors.fill: parent
            source: "qrc:/image/background.png"
        }

        Rectangle {
            id: toolBlock
            radius: 6
            width: parent.width
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#AA39C4FF"
            z: 100

            Row {
                id: controlButtons
                width: 68
                height: 40
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 4

                MyButton {
                    id: minButton
                    width: 32
                    height: 32
                    normalImage: "qrc:/image/min_normal.png"
                    pressedImage: "qrc:/image/min_down.png"
                    hoveredImage: "qrc:/image/min_hover.png"

                    onClicked: {
                        root.showMinimized();
                    }
                }

                MyButton {
                    id: closeButton
                    width: 32
                    height: 32
                    normalImage: "qrc:/image/close_normal.png"
                    pressedImage: "qrc:/image/close_down.png"
                    hoveredImage: "qrc:/image/close_hover.png"

                    onClicked: {
                        root.visible = false;
                    }
                }
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "#77ffffff"
            //anchors.margins: 8
            anchors {
                topMargin: 50
                bottomMargin: 8
                leftMargin: 8
                rightMargin: 8
            }

            DocumentHelper {
                id: docHelper
                selectionStart: codeView.selectionStart
                selectionEnd: codeView.selectionEnd
                cursorPosition: codeView.cursorPosition
                highlightColor: "yellow"
                document: codeView.textDocument
            }

            Flickable {
                id: flickable
                flickableDirection: Flickable.VerticalFlick
                anchors.fill: parent

                TextArea.flickable: TextArea {
                    id: codeView
                    font.pointSize: 10
                    color: "black"
                    readOnly: true
                    wrapMode: TextArea.WrapAnywhere
                    selectionColor: "#09A3DC"
                    selectByKeyboard: true
                    selectByMouse: true
                    persistentSelection: true
                    padding: 4
                    background: null
                }

                ScrollBar.vertical: ScrollBar {
                    id: scrollBar
                    width: 14
                    hoverEnabled: true
                    active: hovered || pressed
                    contentItem: Rectangle {
                        radius: 4
                        visible: scrollBar.active
                        width: scrollBar.width
                        height: scrollBar.height
                        color: scrollBar.hovered ? Qt.lighter("#39C4FF", 1.2) : Qt.lighter("#39C4FF", 1.1)
                    }
                }
            }
        }
    }
}

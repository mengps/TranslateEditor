import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import Qt.labs.platform 1.1
//import QtQuick.XmlListModel 2.13
import an.window 1.0
import an.model 1.0

FramelessWindow {
    id: rootWindow
    visible: true
    width: 780
    height: 540
    title: qsTr("Translate Editor")

    property CodeWindow codeWindow: CodeWindow {
        width: 600
        height: 600
        onEntered: codeWindowTimer.stop();
    }
    property color mainColor: "#FF9968"
    property url currentFile: ""
    property url currentFolder: ""

    function creatCodeWindow(x, y, w, h) {
        var component = Qt.createComponent("CodeWindow.qml", rootWindow);
        if (component.status === Component.Ready) {
            var window = component.createObject(rootWindow,
                                                { "x": x, "y": y, "width": w, "height": h });
        }
        codeWindow = window;
    }

    Rectangle {
        anchors.fill: parent
        color: listView.dataColor
        radius: 4
    }

    Rectangle {
        id: toolBlock
        radius: 4
        width: parent.width
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        color: rootWindow.mainColor
        z: 100

        ReelMenu {
            id: fileMenu
            menuWidth: 80
            menuHeight: 34
            reduceColor: Qt.lighter(rootWindow.mainColor, 1.3)
            expandColor: reduceColor
            text: qsTr("File")
            anchors {
                left: parent.left
                leftMargin: 50
                top: parent.top
                topMargin: 8
            }

            ReelSeparator {
                color: "#fff"
            }

            ReelAction {
                text: qsTr("Open [.ts]")
                height: 34
                color: hovered ? Qt.darker(parent.expandColor, 1.05)
                               : parent.expandColor
                onClicked: openDialog.open();

                FileDialog {
                    id: openDialog
                    title: qsTr("Please choose a TS file")
                    folder: StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]
                    nameFilters: [ qsTr("TS files (*.ts *.TS)") ]
                    onAccepted: {
                        if (tsModel.load(openDialog.file)) {
                            adText.visible = true;
                            rootWindow.currentFolder = folder;
                        }
                    }
                }
            }

            ReelSeparator {
                color: "#fff"
            }

            ReelAction {
                text: qsTr("Save [.ts]")
                height: 34
                color: hovered ? Qt.darker(parent.expandColor, 1.05)
                               : parent.expandColor
                onClicked: saveDialog.open();

                FileDialog {
                    id: saveDialog
                    title: qsTr("Please Save to TS file")
                    fileMode: FileDialog.SaveFile
                    folder: rootWindow.currentFolder.length == 0
                            ? StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]
                            : rootWindow.currentFolder
                    nameFilters: [ qsTr("TS files (*.ts *.TS)") ]
                    onAccepted: {
                        print(saveDialog.file)
                        tsModel.save(saveDialog.file);
                    }
                }
            }
        }

        ReelMenu {
            id: toolMenu
            menuWidth: 80
            menuHeight: 34
            reduceColor: Qt.lighter(rootWindow.mainColor, 1.3)
            expandColor: reduceColor
            text: qsTr("Tool")
            anchors {
                left: fileMenu.right
                leftMargin: 20
                top: fileMenu.top
            }

            ReelSeparator {
                color: "#fff"
            }

            ReelAction {
                text: qsTr("Create [.qm]")
                height: 34
                color: hovered ? Qt.darker(parent.expandColor, 1.05)
                               : parent.expandColor
            }
        }

        ReelMenu {
            id: settingMenu
            menuWidth: 80
            menuHeight: 34
            reduceColor: Qt.lighter(rootWindow.mainColor, 1.3)
            expandColor: reduceColor
            text: qsTr("Setting")
            anchors {
                left: toolMenu.right
                leftMargin: 20
                top: toolMenu.top
            }

            ReelSeparator {
                color: "#fff"
            }

            ReelAction {
                text: qsTr("Qt Location")
                height: 34
                color: hovered ? Qt.darker(parent.expandColor, 1.05)
                               : parent.expandColor


            }
        }

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
                    rootWindow.showMinimized();
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
                    rootWindow.codeWindow.close();
                    rootWindow.close();
                }
            }
        }
    }

    Rectangle {
        id: dataBackground
        width: parent.width - 10
        anchors.top: toolBlock.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        border.color: listView.headerBorderColor
        color: listView.dataColor

        /** 打个小广告 **/
        Text {
            id: adText
            y: 66
            visible: false
            color: rootWindow.mainColor
            font.pointSize: 24
            lineHeight: 1.2
            text: "公众号【程序梦】\nC/C++/Qt/Qml/OpenGL/FFmpeg\n目前随缘更新，分享，欢迎关注\n_(:3 」∠)_ -･･*'``*:.｡. .｡.:*･゜ﾟ･*☆..."
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        /**
         * 废弃的方案
         * XmlListModel提供只读模型，无法更改，可惜
         */
        /*XmlListModel {
            id: tsModel
            source: "file:///D:/program/TranslateEditor/test/Translator_widget_zh_CN.ts"
            query: "/TS/context/message"

            XmlRole { name: "line"; query: "data(location/@*)[2]" }
            XmlRole { name: "filename"; query: "data(location/@*)[1]" }
            XmlRole { name: "source"; query: "source/string()" }
            XmlRole { name: "type"; query: "translation/@type/string()" }
        }*/

        Rectangle {
            id: listHeader
            anchors.top: parent.top
            border.width: 2
            border.color: listView.headerBorderColor
            width: listView.rowWidth
            height: 50
            z: 100

            Row {
                anchors.fill: parent
                spacing: -1

                Rectangle {
                    width: listView.detailWidth
                    border.color: listView.headerBorderColor
                    height: parent.height
                    color: listView.dataColor

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Show Details")
                    }
                }

                Rectangle {
                    width: listView.columnWidth
                    border.color: listView.headerBorderColor
                    height: parent.height
                    color: listView.dataColor

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Location")
                    }
                }

                Rectangle {
                    width: listView.columnWidth
                    border.color: listView.headerBorderColor
                    height: parent.height
                    color: listView.dataColor

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Source Text")
                    }
                }

                Rectangle {
                    width: listView.columnWidth + 1
                    border.color: listView.headerBorderColor
                    height: parent.height
                    color: listView.dataColor

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Translate Text")
                    }
                }

                Rectangle {
                    width: listView.columnWidth + 1
                    border.color: listView.headerBorderColor
                    height: parent.height
                    color: listView.dataColor

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Comment Text")
                    }
                }
            }
        }

        Timer {
            id: codeWindowTimer
            interval: 800
            running: false
            onTriggered: {
                codeWindow.visible = false;
            }
        }

        Component {
            id: delegate

            Rectangle {
                id: wrapper
                y: -1
                border.color: "gray"
                width: listView.rowWidth
                height: listView.rowHeight

                /**
                 * 此MouseArea实现扩展行高度(粗略实现)
                 */
                MouseArea {
                    width: wrapper.width
                    height: 6
                    anchors.bottom: wrapper.bottom
                    hoverEnabled: true

                    property int offsetY: 0

                    onEntered: {
                        cursorShape = Qt.SizeVerCursor;
                    }
                    onExited: cursorShape = Qt.ArrowCursor;
                    onPressed: {
                        listView.interactive = false;
                        offsetY = mouseY;
                    }
                    onPositionChanged: {
                        if(pressed) {
                            var _y = mouse.y - offsetY;
                            if ((wrapper.height + _y) <= listView.rowHeight)
                                wrapper.height = listView.rowHeight;
                            else wrapper.height += _y;
                        }
                    }
                    onReleased: listView.interactive = true;
                }

                Row {
                    anchors.fill: parent
                    spacing: -1

                    Rectangle {
                        width: listView.detailWidth
                        border.color: listView.dataBorderColor
                        height: wrapper.height
                        color: listView.dataColor

                        CodeButton {
                            anchors.centerIn: parent
                            borderColor: rootWindow.mainColor
                            onHoveredChanged: {
                                if (hovered) {
                                    codeWindowTimer.stop();
                                    codeWindow.x = rootWindow.x + 120;
                                    codeWindow.y = rootWindow.y + 40;
                                    codeWindow.fileNames = fileNames;
                                    codeWindow.lines = lines;
                                    codeWindow.fadeIn();
                                } else {
                                    codeWindowTimer.restart();
                                }
                            }
                        }
                    }

                    Rectangle {
                        width: listView.columnWidth
                        border.color: listView.dataBorderColor
                        height: wrapper.height
                        color: listView.dataColor

                        TextArea {
                            anchors {
                                left: parent.left
                                right: parent.right
                                top: parent.top
                                topMargin: 8
                                bottom: parent.bottom
                                bottomMargin: 8
                            }
                            readOnly: true
                            leftPadding: 10
                            rightPadding: 10
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            /**
                             * 拼接代码位置, 格式为： FileName: Line
                             */
                            text: {

                                if (fileNames.length !== lines.length
                                        || (fileNames.length === 0 || lines.length === 0))
                                    return qsTr("Error!");

                                let result = "";
                                for (let i = 0; i < fileNames.length; i++)
                                    result += i >= 1 ? ('\n' + fileNames[i] + ": " + lines[i])
                                                     : (fileNames[i] + ": " + lines[i]);

                                return result;
                            }

                            MyToolTip {
                                visible: parent.hovered
                                text: parent.text
                            }
                        }
                    }

                    Rectangle {
                        width: listView.columnWidth
                        border.color: listView.dataBorderColor
                        height: wrapper.height
                        color: listView.dataColor

                        MyTextArea {
                            anchors {
                                left: parent.left
                                right: parent.right
                                top: parent.top
                                topMargin: 8
                                bottom: parent.bottom
                                bottomMargin: 8
                            }
                            text: sourceText
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            MyToolTip {
                                visible: parent.hovered
                                text: parent.text
                            }
                        }
                    }

                    Rectangle {
                        width: listView.columnWidth + 1
                        border.color: listView.dataBorderColor
                        height: wrapper.height
                        color: listView.dataColor

                        MyTextArea {
                            anchors {
                                left: parent.left
                                right: parent.right
                                top: parent.top
                                topMargin: 8
                                bottom: parent.bottom
                                bottomMargin: 8
                            }
                            text: translateText
                            readOnly: false
                            onEditingFinished: {
                                if (text.length != 0)
                                    tsModel.setData(index, text, TsModel.Translate);
                            }
                        }
                    }

                    Rectangle {
                        width: listView.columnWidth + 1
                        border.color: listView.dataBorderColor
                        height: wrapper.height
                        color: listView.dataColor

                        MyTextArea {
                            anchors {
                                left: parent.left
                                right: parent.right
                                top: parent.top
                                topMargin: 8
                                bottom: parent.bottom
                                bottomMargin: 8
                            }
                            text: commentsText
                            readOnly: false
                            onEditingFinished: {
                                if (text.length != 0)
                                    tsModel.setData(index, text, TsModel.Comment);
                            }
                        }
                    }
                }
            }
        }

        ListView {
            id: listView
            anchors {
                left: parent.left
                right: parent.right
                top: listHeader.bottom
                topMargin: -1
                bottom: parent.bottom
            }
            model: tsModel
            //header: headerDelegate
            delegate: delegate
            spacing: -1
            clip: true

            property int rowWidth: width - scrollBar.width
            property int detailWidth: 100
            property int columnWidth: (width - detailWidth - scrollBar.width) / 4 + 1
            property int rowHeight: 40
            property color headerBorderColor: "#FF9968"
            property color dataColor: "#F2FEFF"
            property color dataBorderColor: "black"

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
                    color: scrollBar.hovered ? Qt.lighter(rootWindow.mainColor, 1.2)
                                             : Qt.lighter(rootWindow.mainColor, 1.1)
                }
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: parent.dataBorderColor
            }
        }
    }
}


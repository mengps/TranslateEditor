import QtQuick 2.13
import QtQuick.Controls 2.13

Flickable {
    id: flickable
    flickableDirection: Flickable.VerticalFlick
    anchors.fill: parent

    signal editingFinished();

    //property bool followCursor: false
    property alias font: textArea.font
    property alias hovered: textArea.hovered
    property alias readOnly: textArea.readOnly
    property alias text: textArea.text
    property alias horizontalAlignment: textArea.horizontalAlignment
    property alias verticalAlignment: textArea.verticalAlignment

    TextArea.flickable: TextArea {
        id: textArea
        clip: true
        leftPadding: 10
        rightPadding: 10
        readOnly: true
        selectionColor: "#09A3DC"
        selectByKeyboard: true
        selectByMouse: true
        wrapMode: TextEdit.WordWrap

        /**
         * 实现跟随光标，发现有问题
         * Flickable提供此功能
         */
        /*onTextChanged: {
            if (flickable.followCursor)
                flickable.contentY = -cursorRectangle.y + cursorRectangle.height
        }*/

        onEditingFinished: flickable.editingFinished();
    }
}

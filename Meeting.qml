import QtQuick

Rectangle {
    anchors.fill: parent
    color: "#FDD9B5"

    Text {
        text: "Meeting"
        color: "white"
        font.family: "Helvetica";
        font.bold: true
        anchors.right: parent.right
        anchors.margins: dp(50)
        font.pixelSize: dp(30)

        renderType: Text.NativeRendering
    }
}

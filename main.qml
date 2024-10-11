import QtQuick //*QML module not found (QtQuick).*
import QtQuick.Window //*QML module not found (QtQuick.Window).*
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    width: 393
    height: 720
    visible: true
    title: qsTr("Hello World")

    // Пересчёт независимых от плотности пикселей в физические пиксели устройства
    readonly property int dpi: Screen.pixelDensity * 25.4
    function dp(x){ return (dpi < 120) ? x : x * (dpi/160); }

    // Application Bar
    Rectangle {
        id: menuRect
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: dp(48)
        color: "#9FC2CC"

        Row
        {
            id: header
            topPadding: dp(15)
            spacing: dp(15)

            anchors.top: parent.top
            anchors.bottom: parent.bottom

            // Гамбургер Menu
            Rectangle {

                id: menuButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                width: dp(48)
                color: menuRect.color

                Column{
                    padding: dp(15)
                    spacing: dp(7)

                    Rectangle{
                        width: dp(20)
                        height: dp(2)
                    }
                    Rectangle {
                        width: dp(20)
                        height: dp(2)
                    }
                    Rectangle {
                        width: dp(20)
                        height: dp(2)
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: (mouse)=> {
                                   console.log("Button clicked");
                                   nav.toggle()
                                }
                }
            }
            Text {
                id: menuText
                property string textMenu: "text menu"
                leftPadding: (root.width - menuButton.width) / 3.5
                text: qsTr(textMenu)
                color: "white"
                font.pixelSize: dp(20)
                renderType: Text.NativeRendering
            }
        }
    }



    // Loader для смены Фрагментов
    Loader {
        id: loader
        anchors.top: menuRect.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "Meeting.qml"
        property string typeFile: ".qml"
        property string nameFile: ""

        // Функция для смены содержимого Loader
        function loadFragment(index){
            switch(index){
            case 0:
                nameFile = "Meeting"
                break;
            case 1:
                nameFile = "Fragment2"
                break;
            case 2:
                nameFile = "Fragment3"
                break;
            default:
                nameFile = "Fragment4"
                break;
            }

            loader.source = nameFile + typeFile
            menuText.text = nameFile

            // закрываем меню после нажатия
            nav.toggle()
        }
    }

    NavigationDrawer {
        id: nav
        Rectangle {
            anchors.fill: parent
            color: menuRect.color

            // Список с пунктами меню
            ListView {
                anchors.fill: parent

                delegate: Item {
                    height: dp(48)

                    anchors.left: parent.left
                    anchors.right: parent.right

                    Rectangle {
                        id: menuButtonItem
                        anchors.fill: parent
                        anchors.margins: dp(5)
                        color: "#FDD9B5"

                        radius: dp(10)
                        // border: dp(3)

                        Text {
                            text: fragment
                            anchors.fill: parent
                            font.pixelSize: dp(20)

                            renderType: Text.NativeRendering
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        MouseArea {
                            anchors.fill: parent

                            // По нажатию на пункт меню заменяем компонент в Loader
                            onClicked: {
                                loader.loadFragment(index)
                            }
                        }
                    }
                }

                model: navModel
            }
        }
    }

    // Модель данных для списка с пунктами меню
    ListModel {
        id: navModel
        ListElement {fragment: "Meeting"}
        ListElement {fragment: "Fragment 2"}
        ListElement {fragment: "Fragment 3"}
    }

}


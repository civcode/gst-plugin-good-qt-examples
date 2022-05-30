import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.1

import org.freedesktop.gstreamer.GLVideoItem 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480
    color: "black"

    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height

//    menuBar: MenuBar {

//    }

    Item {
        anchors.fill: parent

        GstGLVideoItem {
            id: video
            objectName: "videoItem"
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
        }
    }

    MouseArea {
        id: mousearea
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            openPopup()
        }
        onEntered: {
            openPopup()
        }
        function openPopup() {
            popup.open()
            hidetimer.start()
        }
    }

    Popup {
        id: popup
        width: parent.width - 30
        height: parent.height - 30
        anchors.centerIn: parent

        background: Rectangle {
            color: Qt.rgba(30/255, 144/255, 1, 0.8)
            border.width: 1
            border.color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width : video.width - 30
            height: video.height - 30
            radius: 8

        }

        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside

        Timer {
            id: hidetimer
            interval: 2000
            onTriggered: {
                popup.close()
                stop()
            }
        }

        ColumnLayout {
            //Layout.preferredHeight: 50
            id: columnLayoutId
            property int buttonHeight: 45

            x: parent.x + 10
            y: parent.y + 10
            Button {
                Layout.preferredHeight: columnLayoutId.buttonHeight
                text: "Default"
                onClicked: {
                    hidetimer.restart()
                    console.log("clicked")
                    //MyTimer.onButtonPressed()
                    MyTimer.button(0)
                }
            }
            Button {
                Layout.preferredHeight: columnLayoutId.buttonHeight
                text: "Ball"
                onClicked: {
                    hidetimer.restart()
                    MyTimer.button(1)
                }
            }
            Button {
                Layout.preferredHeight: columnLayoutId.buttonHeight
                text: "Quit"
                onClicked: Qt.quit()
            }
        }




    }

    Rectangle {
        id: rectId
        //color: Qt.rgba(1, 1, 1, 0.7)
        color: Qt.rgba(30/255, 144/255, 1, 0.8)
        //color: "dodgerblue"
        border.width: 1
        border.color: "white"
        //anchors.bottom: video.bottom
        //anchors.bottomMargin: 15
        //anchors.top: video.top
        //anchors.topMargin: 15
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        //width : parent.width - 30
        //height: parent.height - 30
        width : video.width - 30
        height: video.height - 30
        radius: 8



//        MouseArea {
//            id: popupMousearea
//            anchors.fill: parent
//            hoverEnabled: true
//            onEntered: {
//                setRectVisibility()
//            }
//            onPositionChanged: {
//                setRectVisibility()
//            }

//            function setRectVisibility() {
//                rectId.opacity = 1.0
//                hidetimer.stop()
//                hidetimer.start()
//                rectId.focus = true
//            }
//        }

//        Timer {
//            id: hidetimer
//            interval: 2000
//            onTriggered: {
//                rectId.opacity = 0.0
//                rectId.focus = false
//                stop()
//            }
//        }

//        ColumnLayout {
//            //Layout.preferredHeight: 50
//            id: columnLayoutId
//            property int buttonHeight: 45

//            x: parent.x + 10
//            y: parent.y + 10
//            Button {
//                Layout.preferredHeight: columnLayoutId.buttonHeight
//                text: "Default"
//                onClicked: {
//                    console.log("clicked")
//                    //MyTimer.onButtonPressed()
//                    MyTimer.button(0)
//                }
//            }
//            Button {
//                Layout.preferredHeight: columnLayoutId.buttonHeight
//                text: "Ball"
//                onClicked: {
//                    MyTimer.button(1)
//                }
//            }
//            Button {
//                Layout.preferredHeight: columnLayoutId.buttonHeight
//                text: "Quit"
//                onClicked: Qt.quit()
//            }
//        }


    }
    onOpenglContextCreated: {
        rectId.opacity = 0.0
        //hidetimer.start()
    }



}

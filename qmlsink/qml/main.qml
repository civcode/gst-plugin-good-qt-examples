import QtQuick 2.4
import QtQuick.Controls 1.1
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
    x: 30
    y: 30
    color: "black"

    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height

    Item {
        anchors.fill: parent

        GstGLVideoItem {
            id: video
            objectName: "videoItem"
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
        }

        Rectangle {
            id: rectId
            //color: Qt.rgba(1, 1, 1, 0.7)
            color: Qt.rgba(30/255, 144/255, 1, 0.8)
            //color: "dodgerblue"
            border.width: 1
            border.color: "white"
            anchors.bottom: video.bottom
            anchors.bottomMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            width : parent.width - 30
            height: parent.height - 30
            radius: 8


            MouseArea {
                id: mousearea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    setRectVisibility()
                }
//                onClicked: {
//                    //parent.opacity = 1.0
//                    //hidetimer.stop()
//                    //hidetimer.start()
//                    setRectVisibility()
//                }
                onPositionChanged: {
                    setRectVisibility()
                }

                function setRectVisibility() {
                    rectId.opacity = 1.0
                    hidetimer.stop()
                    hidetimer.start()
                }
            }

            Timer {
                id: hidetimer
                interval: 2000
                onTriggered: {
                    parent.opacity = 0.0
                    stop()
                }
            }

            ColumnLayout {
                x: parent.x + 10
                y: parent.y + 10
                Button {
                    text: "default"
                    onClicked: {
                        console.log("clicked")
                        //MyTimer.onButtonPressed()
                        MyTimer.button(0)
                    }
                }
                Button {
                    text: "ball"
                    onClicked: {
                        MyTimer.button(1)
                    }
                }
            }


        }


    }
    onOpenglContextCreated: {
        rectId.opacity = 0.0
        //hidetimer.start()
    }

}

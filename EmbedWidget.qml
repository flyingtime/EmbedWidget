import QtQuick 2.7
import QtQuick.Window 2.2

Item{
    id: item
    property int someNumber: 100
    signal qmlSignal(string msg)
    width: 1280
    height: 720

    Rectangle{
        x:100
        y:20
        width: 800
        height: 610
        color:"steelblue"
        objectName: "videoPlugin"
        //anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: item.qmlSignal("Hello from QML")
    }
}

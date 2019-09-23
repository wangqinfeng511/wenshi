import QtQuick 2.0
import QtQuick.Window 2.0
//import QtQuick.
Rectangle{
    id:root
    anchors.fill: parent
    signal select_dom(var mac)
    property var root_dom //main.qml传入的main
    property var select_wifi_ssid
    color: Qt.rgba(0,0,0,1)
    radius: 5
    MouseArea{
        anchors.fill: parent
    }
    Component.onCompleted: {
        var aps=Wifi.get_ssid();
        var keys=Object.keys(aps);
        for (var i=0;i<keys.length;i++){
            data_model.append(aps[keys[i]])
        }
    }
    ListModel{
        id:data_model
    }
    Rectangle{
        id:box
        width: root.width/2
        height: root.height*0.9
        anchors.centerIn: parent
        radius: 5
        color: Qt.rgba(0.1,0.1,0.1,1)
        Column{
            spacing: 15
        Item {
            id:title
            width: root.width*0.5
            height: root.height*0.1
//            border.color: Qt.rgba(1,0,0,1)
            anchors.left: parent.left
//            anchors.top: parent.top
            anchors.leftMargin: 10
            Image {
                id:wifi_logo
                width: title.height*0.8
                height: title.height*0.8
                anchors.verticalCenter: parent.verticalCenter
//                anchors.top: parent.top
//                anchors.topMargin: 5
                source: "qrc:/static/img/OK.png"
                        }
             Column{
                anchors.left: parent.left
                anchors.leftMargin: wifi_logo.width+5
                Text {
                    font.family: "FZSJ-ZJYTJW"
                    font.pixelSize: 18
                    color: Qt.rgba(0.9,0.9,0.9,1)
                    text: qsTr("Wifi网络")
                    }
                 Text {
                     font.family: "FZSJ-ZJYTJW"
                     color: Qt.rgba(0.9,0.9,0.9,1)
                     font.pixelSize: 18
                     text: qsTr("选择网络")
                        }
                      }
                    }
        Rectangle{
            width: box.width*0.8
            height: box.width*0.8
            color: Qt.rgba(0,0,0,0)
            border.color: Qt.rgba(0.3,0.3,0.3,1);
            border.width: 1;
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 5
            ListView{
                spacing: 3
                model: data_model
                anchors.fill: parent
                clip: true
                delegate:dom
            }
        }
       }
        Component{
            id:dom
            Rectangle{
                id:dom_box
                width: box.width*0.75
                height: 40
                color: Qt.rgba(0.4,0.4,0.4,1)
                anchors.horizontalCenter: parent.horizontalCenter
                radius: 5
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        root.select_dom(wifi_mac)
                    }
                }
                Connections{
                    target: root
                    onSelect_dom:{
                        if(mac===wifi_mac){
                            dom_box.color=Qt.rgba(1,0.6,0.6,1)
                            root.select_wifi_ssid=ssid
                        }else{
                            dom_box.color=Qt.rgba(0.4,0.4,0.4,1);
                        }
                    }
                }
                Text {
                    anchors.left: parent.left
                        font.family: "FZSJ-ZJYTJW"
                        color: Qt.rgba(1,1,1,1)
                        font.pixelSize: 20
                        text: {
                            String(ssid).substring(0,8);
                        }
                  }
                Image {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    id: suo
                    width: 20
                    height: 20
                    source: "qrc:/static/img/lock.png"
                    }
                }
        }
        //取消
        Rectangle{
            anchors.bottom: parent.bottom
            width: box.width/2*0.9
            anchors.left: parent.left
            height: box.height*0.15
            color: Qt.rgba(0.4,0.4,0.4,1)
            radius: 5
            MouseArea{
                anchors.fill: parent
                onClicked:  {
                        root.destroy();
                 }
             }
            Text {
                text: qsTr("取消")
                color: Qt.rgba(1,1,1,1)
                anchors.centerIn: parent;
            }
        }
        //连接
        Rectangle{
            anchors.bottom: parent.bottom
            width: box.width/2*0.9
            anchors.right: parent.right
            height: box.height*0.15
            color: Qt.rgba(0.4,0.4,0.4,1)
            radius: 5
            MouseArea{
                anchors.fill: parent
                onClicked:  {
                    if(root.select_wifi_ssid){
                        var com= Qt.createComponent("Connect_wifi.qml")
                        com.createObject(root.root_dom,{"width":root.width,"height":root.height,"select_wifi_dom":root});
                    }
//                        root.destroy();
                 }
             }
            Text {
                text: qsTr("连接")
                color: Qt.rgba(1,1,1,1)
                anchors.centerIn: parent;
            }
        }
    }
}

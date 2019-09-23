import QtQuick 2.4
import QtQuick.Window 2.2
import Dcb 1.0
import Date_time_dial 1.0;
Window {
    id:root
    visible: true
    width: 480
    height: 320
    color: Qt.rgba(0,0,0,1)
    title: qsTr("Hello World")
    property var  desplay_dom;
    Date_time_dial{
        id:kedu
        width: root.height
        height: root.height
        anchors.centerIn: parent
    }
    FontLoader{
        id:font_id
        source: "qrc:/static/font/digifaw.ttf"
    }
    FontLoader{
        source: "qrc:/static/font/FZSJ-ZJYTJW.TTF"
    }
    Image {
        id: wifi
        source: "qrc:/static/img/dconnect.png"
        width: 40
        height: 40
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10
        MouseArea{
            anchors.fill: parent
            onPressed: {
//                if(root.desplay_dom===null ||root.desplay_dom===undefined){
//                                    console.log(root.desplay_dom);
                var select_wifi_compent=Qt.createComponent("Select_wifi.qml")
                select_wifi_compent.createObject(root,{root_dom:root});
//                   root.desplay_dom=select_wifi_compent.createObject(root,{"width":root.width,"height":root.height});
//                }
            }

        }
    }
    Dcb{
        id:bj
        width: kedu.width*0.5
        height: kedu.height*0.5
        anchors.centerIn: parent
//        visible: false
        Text {
            text: qsTr("时间")
            font.family: "FZSJ-ZJYTJW"
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top
            font.pixelSize: 30
            color: Qt.rgba(0.1,0.1,0.1,1)
            anchors.topMargin: font.pixelSize*0.5;
        }
        Text {
            id:date_time
            text: "02"+":"+"23"
            font.family: "DigifaceWide";
            font.pixelSize: 40
            color: Qt.rgba(0.1,0.1,0.1,1)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: bj.height*0.2
        }
        Text {
            id: wendu_teget
            text: qsTr("温度℃")
            font.family: "FZSJ-ZJYTJW"
            font.pixelSize: 20
            anchors.left: parent.left
            anchors.leftMargin: bj.width/2*0.1
            color: Qt.rgba(0.7,0.7,0.7,1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin:bj.height/2-font.pixelSize*1.3
        }
        Text {
            id: wendu_value
            text: "0";
            color: Qt.rgba(0.7,0.7,0.7,1)
            anchors.left: parent.left
            anchors.leftMargin: (bj.width/4-font.pixelSize/2)*0.8
            font.pixelSize: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: bj.height/2-font.pixelSize*2
        }
        Text {
            id: shidu_teget
            text: qsTr("湿度%")
            font.pixelSize: 20
            anchors.right: parent.right
            anchors.rightMargin:bj.width*0.1
            color: Qt.rgba(0.7,0.7,0.7,1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin:bj.height/2-font.pixelSize*1.3
        }
        Text {
            id: shidu_value
            text: "0";
            color: Qt.rgba(0.7,0.7,0.7,1)
            anchors.right: parent.right
            anchors.rightMargin:bj.width/4-font.pixelSize/2
            font.pixelSize: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: bj.height/2-font.pixelSize*2
        }
    }
    Connections{
        target: Api
        onDate_time_update:{
            kedu.shi=data["shi"];
            kedu.update();
            date_time.text=data["fen"]+":"+data["miao"]
            if(data["wendu"]>0){
            wendu_value.text=data["wendu"];
            shidu_value.text=data["shidu"];
            }

        }
    }
    Connections{
        target: Wifi
        onUpdate_status:{
            if(Object.keys(status).length>0){
//                if(status["wpa_state"]=="")
                if(status["wpa_state"]==="COMPLETED"){
                    wifi.source="qrc:/static/img/OK.png"
                }
            }
        }
    }
}

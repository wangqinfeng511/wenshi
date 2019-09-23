import QtQuick 2.0
//import QtQuick.VirtualKeyboard 2.2
import QtQuick.VirtualKeyboard 2.3
Rectangle{
    id:root
    color:Qt.rgba(0,0,0,1)
    property var select_wifi_dom
    anchors.fill: parent
    Rectangle{
        id:password
        width: root.width*0.8
        height: root.height*0.5
//        anchors.centerIn: parent
        x:(root.width-password.width)/2
        y:(root.height-password.height)/2
        color:Qt.rgba(0,0,0,1)
        radius: 5
        border.color: Qt.rgba(1,1,1,1)
        border.width: 1
//        MouseArea{
//            anchors.fill: parent
//            onPressed: {
//                root.destroy()
//            }
//        }
        Image {
            id: yaoshi
            width: 40
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 2.5
            anchors.top: parent.top
            anchors.topMargin: 20
            source: "qrc:/static/img/yaoshi.png"
        }
        Item {
            width: password.width*0.8
            height: password.height
            anchors.left: parent.left;
            anchors.leftMargin: 45
            anchors.top: parent.top
            anchors.topMargin: 10
//            anchors.horizontalCenter: parent.horizontalCenter
            Column{
                spacing: 10
                Text {
                    text: qsTr("无线网络要求身法认证");
                    color: Qt.rgba(1,1,1,1)
                }
                Text {
                    text: "访问无线网络"+"\""+ String(root.select_wifi_dom.select_wifi_ssid).substring(0,10)+"\""+"需要密码或密钥"
                    color: Qt.rgba(1,1,1,1)
                }
                Row{
                    spacing: 30
                    Text {
                        text: qsTr("密码:")
                        color: Qt.rgba(1,1,1,1)
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle{
                        width: password.width*0.5
                        height: 35
                        border.color: Qt.rgba(0,0,0,1)
                        border.width: 1
                        radius: 3
                        TextInput{
                            id:input_box
                            anchors.fill: parent
//                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            onFocusChanged: {
                                if(input_box.focus){
                                    vkb.visible=true
                                    password.y-=30
                                }

                            }
                        }
                    }

                }
            }

        }
        Item{
            //取消
            width: password.width
            height: password.height*0.3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            Rectangle{
                anchors.bottom: parent.bottom
                width: password.width/2*0.9
                anchors.left: parent.left
                height: password.height*0.3
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
                width: password.width/2*0.9
                anchors.right: parent.right
                height: password.height*0.3
                color: Qt.rgba(0.4,0.4,0.4,1)
                radius: 5
                MouseArea{
                    anchors.fill: parent
                    onClicked:  {
//                                if(root.select_wifi_ssid){
//                                    var com= Qt.createComponent("Connect_wifi.qml")
//                                    com.createObject(root.root_dom,{"width":root.width,"height":root.height,"select_wifi_dom":root});
//                                }
                                root.destroy();
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
    InputPanel{
        id: vkb
        visible: false
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        //这种集成方式下点击隐藏键盘的按钮是没有效果的，
        //只会改变active，因此我们自己处理一下
        onActiveChanged: {
            if(!active) { visible = false;
//                password.y+=30
                input_box.focus=false
                root.destroy();
            }
        }
    }

}

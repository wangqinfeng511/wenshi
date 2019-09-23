#include "wifi.h"
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include<QString>
#include <QJsonObject>
#include <QTimer>
wifi::wifi(QObject *parent) : QObject(parent)
{
    QTimer *wifi_status_ds=new QTimer();
    connect(wifi_status_ds,SIGNAL(timeout()),this,SLOT(get_status()));
    wifi_status_ds->start(500);
}
QJsonObject wifi::get_ssid(){
    QJsonObject data;
    QJsonObject tmp_ap_info;
    QProcess get;
    QString ssid;
    if(get.state()==QProcess::NotRunning){
        get.start("/sbin/wpa_cli",QStringList()<<"-i"<<"wlan0"<<"scan");
        get.waitForReadyRead(10000);
        if(get.exitCode()==0){
         }else {
            qDebug()<<"Error!";
            data.insert("status","Not device");
        }
        get.close();
        get.start("/sbin/wpa_cli",QStringList()<<"-i"<<"wlan0"<<"scan_results");
        get.waitForReadyRead(3000);
        QString aps_all=get.readAll();
        get.close();
//        qDebug()<<aps_all;
        QStringList aps_list=aps_all.split("\n");
        QString ap;
        QStringList Ap_Field;
        for(int i=0;i<aps_list.length();i++){
            if(i==0){
                continue;
            }
           ap=aps_list[i];
           Ap_Field=ap.split("\t");
           if(Ap_Field.length()==5){
               tmp_ap_info.insert("wifi_mac",Ap_Field[0]);
               tmp_ap_info.insert("frequency",Ap_Field[1]);
               tmp_ap_info.insert("signal_level",Ap_Field[2]);
               tmp_ap_info.insert("flags",Ap_Field[3]);
               get.start("/bin/echo",QStringList()<<"-e"<<Ap_Field[4]);
               get.waitForReadyRead(3000);
               ap=QString::fromUtf8(get.readAll()).split("\n")[0];
               tmp_ap_info.insert("ssid",ap);
               get.close();
               if(ap.length()>0){
                   data.insert(ap,tmp_ap_info);
               }

           }
        }

    }
//    qDebug()<<data;
    return data;
}
void wifi::get_status(){
            //获取连接状态
        QJsonObject data;
        QJsonObject tmp_ap_info;
        QProcess get;
        QString ssid;
        get.start("/sbin/wpa_cli",QStringList()<<"-i"<<"wlan0"<<"status");
        get.waitForReadyRead(3000);
            QJsonObject status_data;
            QString wifi_status_str=get.readAll();
            QStringList wifi_status_str_list= wifi_status_str.split("\n");
            for(int i=0;i<wifi_status_str_list.length()-1;i++){
               QStringList tmp=wifi_status_str_list[i].split("\\");
               for(int x=0;x<tmp.length();x++){
                    QStringList tmp_str=tmp[x].split("=");
                    data.insert(tmp_str[0],tmp_str[1]);
               }
            }
            get.close();
            update_status(data);
}
//void update_status(QJsonObject status);
// DISCONNECTED COMPLETED


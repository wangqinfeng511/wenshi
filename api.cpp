#include "api.h"
#include <QTimer>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <wiringPi.h>
Api::Api(QObject *parent) : QObject(parent){
//ubuntu
        get_wen_shi();
    QTimer *while_sleep=new QTimer();
    connect(while_sleep,SIGNAL(timeout()),this,SLOT(get_time()));
    while_sleep->start(1000);
    //ubuntu
    QTimer *while_wenshi=new QTimer();
    connect(while_wenshi,SIGNAL(timeout()),this,SLOT(get_wen_shi()));
    while_wenshi->start(5000);

}
void Api::get_time(){
    QDateTime date_time=QDateTime::currentDateTime();
    QJsonObject date_time_data;
    date_time_data.insert("shi",date_time.toString("hh").toInt());
    date_time_data.insert("fen",date_time.toString("mm").toInt());
    date_time_data.insert("miao",date_time.toString("ss").toInt());
    if(w_s.error=="NULL"){
        date_time_data.insert("wendu",w_s.wen);
        date_time_data.insert("shidu",w_s.shi);
    }else {
        //写入错误日志
    }
    date_time_update(date_time_data);
}
//ubuntu
wen_shi Api::get_wen_shi(){
    wiringPiSetup();
       int pin=27;
       int sleep=10000;
       pinMode(pin,INPUT);
       while (digitalRead(pin)!=HIGH) {
           w_s.error="设备未就绪";
           delay(18);
       }
       pinMode(pin,OUTPUT);
       digitalWrite(pin,LOW);
       delay(18);
       digitalWrite(pin,HIGH);
       delayMicroseconds(30);

   //    pullUpDnControl(pin, PUD_UP);

       //接收数据部分
       pinMode(pin,INPUT);
       delayMicroseconds(27);
       uint8_t tmp_data=0x00; //临时存8bit值
       uint8_t data[5];
       sleep=10000;
       while (sleep>0) {
           if(digitalRead(pin)==LOW){
               break;
           }else {
               w_s.error="初始化失败";
               return w_s;
           }
           if(!(sleep-->0)){
               w_s.error="失败";
               return w_s;
           }
           sleep--;
       }
       sleep=10000;
       while (sleep>0) {
           if(digitalRead(pin)==HIGH){
   //            qDebug()<<"开始传输数据";
               break;
           }
           if(!(sleep-->0)){
               w_s.error="error";
               return w_s;
           }
           sleep--;
           delayMicroseconds(1);
       }
       int i,data_index=0;
       for(i=0;i<40;i++){
           sleep=10000;
           while (sleep>0) {//死守50us的低电平
               if(digitalRead(pin)==LOW) {
                   break;
               }else {
                   sleep--;
               };
           }
           sleep=10000;
           while (sleep>0) {//死守50us低电平过后的高电平
               if(digitalRead(pin)==HIGH) {
                   break;
               }else {
                   sleep--;
               };
           }
           delayMicroseconds(28);
           tmp_data<<=1;
           if(digitalRead(pin)==HIGH){
               tmp_data|=0x01;
           }
           if((i+1)%8==0 and i>0){
               data[data_index]=tmp_data;
               data_index++;
           }

     }
       if(data[0]+data[1]+data[2]+data[3]==data[4]){
           w_s.shi=QString("%1").arg(data[0]);
           QString shi_str=QString::number((QString("%1").arg(data[2])+"."+QString("%1").arg(data[3])).toFloat(),'f',1);
           w_s.wen=QString("%1").arg(data[2]);
           w_s.error="NULL";
//           +"."+QString("%1").arg(data[3]);
//           qDebug()<<w_s.wen<<w_s.shi;
           return w_s;
       }else {
            w_s.error="校验失败";
            return w_s;
        }
};

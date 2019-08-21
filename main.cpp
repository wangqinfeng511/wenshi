#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <wiringPi.h>
#include <QDebug>
#include <QThread>
#include <QString>
int main(int argc, char *argv[])
{
   qputenv("QT_QPA_PLATFORM","eglfs");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    wiringPiSetup();
    int pin=1;
    int sleep=10000;
    pinMode(pin,INPUT);
    while (digitalRead(pin)!=HIGH) {
        qDebug()<<"设备未就绪";
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
//            qDebug()<<"响应信号";
            break;
        }else {
            qDebug()<<"初始化失败";
            return -1;
        }
        if(!(sleep-->0)){
            return -1;
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
            return -1;
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
            qDebug()<<"湿度"<<data[0]<<"温度:"<<QString("%1").arg(data[2])+"."+QString("%1").arg(data[3]);
    }
    return app.exec();
}
//按结构体返回{温度,湿度,错误码}

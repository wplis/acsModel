#include <Wire.h>

unsigned char ch;
unsigned int i;

void setup() {
  // put your setup code here, to run once:
    Wire.begin();
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    Wire.requestFrom(10, 1);
    if(!Wire.available())
        return;
    
    ch=Wire.read();
    Serial.println(ch&15);
    switch(ch>>4)
    {
        case 1:
            ch=Wire.read();
            Serial.println(ch+48);
        break;
        case 2:
            i=Wire.read();
            i=i<<8;
            i+=Wire.read();
            Serial.println(i);
        break;
        case 3:
            ch=Wire.read();
            Serial.println(int(ch));
        break;
        case 4:
            for(ch=0;ch<4;ch++)
                Serial.println(int(Wire.read()));
        break;
        case 5:
            ch=Wire.read();
            Serial.println(int(ch));
        break;
        case 0:
            Serial.println("ERROR!!!");
        break;
    }
    if(Serial.available())
    {
        ch = Serial.read();
        
        switch(ch -=48)
        {
            case 1:
                Serial.println("choise 1");//пинг
                Wire.beginTransmission(10);
                Wire.write(16);//сложить числа
                Wire.write(90);//5 и 10
                Wire.endTransmission();
            break;
            case 2:
                Serial.println("choise 2");//опрос датчика
                Wire.beginTransmission(10);
                Wire.write(32);//опросить датчик 0
                Wire.endTransmission();
            break;
            case 3:
                Serial.println("choise 3");//опрос событий
                Wire.beginTransmission(10);
                Wire.write(52);//запрос 4х событий
                Wire.endTransmission();
            break;
            case 4:
                Serial.println("choise 4");//работа с картой
                Wire.beginTransmission(10);
                Wire.write(65);//добавить в список карту
                Wire.write(255);
                Wire.write(255);
                Wire.write(255);
                Wire.write(255);
                Wire.endTransmission();
            break;
            case 5:
                Serial.println("choise 5");//опрос конфигурации
                Wire.beginTransmission(10);
                Wire.write(80);//запрос конфига а именно id
                Wire.endTransmission();
            break;
            case 6:
                Serial.println("choise 6");//смена конфигурации
                Wire.beginTransmission(10);
                Wire.write(96);//запрос на смену id
                Wire.write(2);//новый id=2
                Wire.endTransmission();
            break;
            case 7:
                Serial.println("choise 7");//действие
                Wire.beginTransmission(10);
                Wire.write(112);//запрос на включение триггера 0
                Wire.write(5);//на 5 секунд
                Wire.endTransmission();
            break;
        }
        Serial.println("iteration");
        //i=Serial.read();
        //ch+=i;
        
        
    }
    delay(2000);
}

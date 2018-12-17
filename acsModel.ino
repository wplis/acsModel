#include "acsmodel.h"

/*
 * Id 0 - без определения
 *    1 - модуль панелей
 *    2 - модуль считывателя RFID
 */


unsigned char str[4] = {'u','p','l','s'};
int i;


accEsser *keyList;
confiGurator *piner;
keyReader *reader;
//transPorter *trans;


void setup() {
    keyList = new accEsser();
    piner = new confiGurator();
    reader = new rfidReader();
//    trans = new transPorter();
//    reader->create(true);
    // put your setup code here, to run once:
    
Serial.begin(9600);
    Serial.println(piner->addTriger(13));
    Serial.print("sensor ");
    Serial.println(piner->addSensor(A0));
    i=0;
}

void loop() {
    //keyList->add(str);
    if(!i)
    {
      i++;
      piner->trigClic(0,5);
    }

    Serial.println(piner->sensor(0));
    delay(500);
    piner->clickControl();

}

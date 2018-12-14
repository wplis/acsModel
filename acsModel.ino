#include "accesser.h"
#include "configurator.h"
#include "keyreader.h"

/*
 * Id 0 - без определения
 *    1 - модуль панелей
 *    2 - модуль считывателя RFID
 */
const bti lengths[3]={0,0,5};

#include "acsmodel.h"



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  static unsigned char memData[10240];
  for(int i=0; i<10240; i++)
    memData[i] = 0;
  // put your main code here, to run repeatedly:

}

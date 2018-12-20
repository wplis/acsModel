#include "accesser.h"
#include "configurator.h"
#include "rfidreader.h"
#include "transporter.h"
#include <EEPROM.h>

#define btc unsigned char
#define bti unsigned int

/*
 * Id 0 - без определения
 *    1 - модуль панелей
 *    2 - модуль считывателя RFID
 */
btc addr, id, panels, i, j, inKey[4];
bti ii;

accEsser *keyList;
confiGurator *piner;
keyReader *reader;
transPorter *trans;
    
void saveConfig()
{
    EEPROM.write(8, id);
    delay(10);
    EEPROM.write(9, addr);
    delay(10);
    EEPROM.write(10, panels);
    delay(10);
}

void loadConfig()
{
    id = EEPROM.read(8);
    addr = EEPROM.read(9);
    panels = EEPROM.read(10);
}

btc calcPing(btc operation, btc first, btc second)
{
    btc answer;

    if(second > first)
    {
        answer = first;
        first = second;
        second = answer;
    }

    switch(operation)
    {
        case 0:
            answer = first + second;
        break;
        case 1:
            answer = first - second;
        break;
        case 2:
            answer = first * second;
        break;
        case 3:
            answer = first / second;
        break;
        default:
            answer = 255;
    }
    return answer;
}
//----------------------------------------------------

void setup() {
    loadConfig();

//    id=0;
//    panels=0;
    
    if(!(0<addr<255))
        addr=10;

    trans = new transPorter(addr);

    switch(id)
    {
        case 2:
            keyList = new accEsser();
            reader = new rfidReader();
            reader->create(panels);
            trans->create(inKey);
        case 1:
            piner = new confiGurator();
        break;
    }
}

void loop() {

//обработка поступлений и ответов по i2c обработка транспортера
    if(trans->isReady(0)) switch(trans->question()[0]>>4)
    {
        case 1://обработка пинга
            i=16;
            i+= trans->countEvents();
            trans->answer()[0] = i;
            trans->answer()[1] = calcPing(trans->question()[0] & 15, trans->question()[1] >> 4, trans->question()[1] && 15);
            
            trans->question()[0] = 0;
            trans->isReady(2);
        break;
        case 2://обработка запроса состояния датчиков
            ii=piner->sensor(trans->question()[0] & 15);
            trans->answer()[0] = 32 + (trans->question()[0] & 15);
            trans->answer()[1] = ii >> 8;
            trans->answer()[2] = ii & 255;
            
            trans->question()[0] = 0;
            trans->isReady(3);
        break;
        case 3://отправка запрошенного количества событий из списка
            if(trans->sendEvent())
                trans->question()[0]--;

            if(!trans->countEvents() || !(trans->question()[0] & 15))
                trans->question()[0]=0;
        break;
        case 4://опрос, добавление или удаление ключа доступа
            i=trans->question()[0] & 15;
            if(!i)
                break;
            if(i==1)
                j=keyList->add(inKey);
            if(i==2)
                j=keyList->del(keyList->findKey(inKey));
            if(i==3)//подготовить ключ к отправке
            {
                for(j=0; j<4; j++)
                    inKey[j] = reader->dataKey(false)[j];
            }
            if(i==4)
            {
                for(j=0; j<4; j++)
                    inKey[j] = reader->dataKey(true)[j];
            }
            if(i < 3)
            {
                ii = 12544+j;
                trans->addEvent(ii);
            }
            else
            {
                trans->answer()[0]=64;
                if(keyList->findKey(inKey) < 255)
                    trans->answer()[0]++;
                trans->isReady(4);
            }
            trans->question()[0] = 0;
        break;
        case 5://опрашиваем конфигурацию
//добавить опрос количества ключей и элементов конфигуратора
            i=trans->question()[0] & 15;
            trans->answer()[0] = 80+i;
            switch(i)
            {
                case 0:
                    trans->answer()[1]=id;
                break;
                case 1:
                    trans->answer()[1]=panels;
                break;
                case 2:
                    trans->answer()[1]=addr;
                break;
            }
            trans->question()[0] = 0;
            trans->isReady(2);
        break;
        case 6://меняем конфигурацию
//добавление триггеров и датчиков в конфигуратор
            i=trans->question()[0] & 15;
            trans->answer()[0] = 96;
            switch(i)
            {
                case 0:
                    id=trans->question()[1];
                break;
                case 1:
                    panels=trans->question()[1];
                break;
                case 2:
                    addr=trans->question()[1];
                break;
            }
            
            saveConfig();
                    
            i=id;
            j=addr;
            loadConfig();
                    
            if(i!=id || j!=addr)
                trans->answer()[0]++;
                
            trans->question()[0] = 0;
            trans->isReady(1);
        break;
        case 7://управление, включаем/выключаем триггер или включаем на время
            i=trans->question()[0]&15;
            j=trans->question()[1];
            ii=12800+i<<4;
            
            if(j)
                j=piner->trigClic(i&7, j);
            else
                j=piner->triger(i&7, i>>3);

            if(j<255)
                ii++;
            trans->addEvent(ii);
        break;
    }
    
    switch(id)
    {
        case 2://обработка считывателя карты
            i=reader->watchKey();
            if(i)
            {
                ii=12288;
                if((i>>4) > 0)//обработка карты на панели 1
                {
                    if((i>>4) > 1)
                        ii+=2;
                    else if(keyList->findKey(reader->dataKey(false)) < 255)
                        ii++;
                    trans->addEvent(ii);
                }
                if((i&15) > 0)//обработка карты на панели 2
                {
                    ii+=16;
                    
                    if((i&15) > 1)
                        ii+=2;
                    else if(keyList->findKey(reader->dataKey(true)) < 255)
                        ii++;
                    trans->addEvent(ii);
                }
        //-----------------------------------
            }
        case 1:
            piner->clickControl();
//проверка состояний датчиков
        break;
    }
}

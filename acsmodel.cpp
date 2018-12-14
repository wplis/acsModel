#include <EEPROM.h>
#include <arduino.h>
#include "acsmodel.h"

acsModel::acsModel()
{
    id = 0;
}

btc acsModel::create(btc newId)
{
    id = newId;
}

btc acsModel::saveConfig()
{
    EEPROM.write(8, id);
    delay(10);
    EEPROM.write(9, addr);
    delay(10);
}

btc acsModel::loadConfig()
{
    id = EEPROM.read(8);
    addr = EEPROM.read(9);

    configure();
}






btc acsModel::configure()
{

}


btc acsModel::shId()
{
    return id;
}

btc acsModel::setAddr(btc newAddr)
{
    addr = newAddr;
    return addr;
}

btc acsModel::calcPing(btc operation, btc first, btc second)
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

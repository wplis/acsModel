#include "acsmodel.h"

acsModel::acsModel(btc newId)
{
    id = newId;

    for(i=0; i<16; i++)
        sensors[i] = 255;
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

btc acsModel::sensor(btc number)
{
    return sensors[number];
}

btc acsModel::addSensor(btc pin)
{
    for(i=0; i<16 && sensors[i]<255; i++);
    if(i>15)
        return 255;
    sensors[i] = pin;

    return i;
}

btc acsModel::delSensor(btc number)
{
    if(number > 15)
        return 255;
    for(i=number; i<15; i++)
        sensors[i] = sensors[i+1];
    sensors[i] = 255;

    return i;
}

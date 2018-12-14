#include <arduino.h>
#include "configurator.h"

confiGurator::confiGurator()
{
    waitTime = 0;
    for(i=0; i<16; i++)
    {
        sensors[i] = 255;
        trigers[i] = 255;
        trigWait[i] = 0;
    }
    for(i=0; i<6; i++)
        intensiv[i] = 255;
}

bti confiGurator::sensor(btc number)
{
    if(sensors[number]<255)
        i=analogRead(sensors[number])*4.8876;
    else
        i=65535;
        
    return i;
}

btc confiGurator::addSensor(btc pin)
{
    for(i=0; i<16 && sensors[i]<255; i++);
    if(i>15)
        return 255;
    sensors[i] = pin;
    pinMode(pin, INPUT);

    return i;
}

btc confiGurator::delSensor(btc number)
{
    if(number > 15)
        return 255;
    for(i=number; i<15; i++)
        sensors[i] = sensors[i+1];
    sensors[i] = 255;

    return i;
}

btc confiGurator::triger(btc number, bool isOn=true)
{
    if(trigers[number]<255)
        digitalWrite(trigers[number], isOn);
    return trigers[number];
}

btc confiGurator::addTriger(btc pin)
{
    for(i=0; i<16 && trigers[i]<255; i++);
    if(i>15)
        return 255;
    trigers[i] = pin;
    pinMode(pin, OUTPUT);

    return i;
}

btc confiGurator::delTriger(btc number)
{
    if(number > 15)
        return 255;
    for(i=number; i<15; i++)
        trigers[i] = trigers[i+1];
    trigers[i] = 255;
    trigWait[i] = 0;

    return i;
}

btc confiGurator::intens(btc number, btc powerInt)
{
    if(intensiv[number]<255)
        analogWrite(intensiv[number], powerInt);
    return intensiv[number];
}

btc confiGurator::addIntens(btc pin)
{
    for(i=0; i<6 && intensiv[i]<255; i++);
    if(i>5)
        return 255;
    intensiv[i] = pin;
    pinMode(pin, OUTPUT);

    return i;
}

btc confiGurator::delIntens(btc number)
{
    if(number > 5)
        return 255;
    for(i=number; i<5; i++)
        intensiv[i] = intensiv[i+1];
    intensiv[i] = 255;

    return i;
}

btc confiGurator::trigClic(btc numTrig, btc timeSec)
{
    if(triger(numTrig) < 255)
        trigWait[numTrig] = timeSec;
    else
        return 255;
    return timeSec;
}

void confiGurator::clickControl()
{
    tmpTime = millis();
    if((tmpTime - waitTime)<1000)
        return;

    waitTime = tmpTime;
    for(i=0; i<16; i++)
    {
        if(trigers[i] == 255)
            return;
        if(trigWait[i])
            trigWait[i]--;
        if(!trigWait[i])
            triger(i, false);
    }
}

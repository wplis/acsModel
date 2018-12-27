#include <Wire.h>
#include "transporter.h"

#include "Arduino.h"

btc eventCount;
btc answerReady;
bti events[16];

btc *transData;
btc inQest[2];
btc outAns[3];

void i2cIncomingCheck();
void i2cPrepareAnswer();

void senderEvent()
{
    i2cPrepareAnswer();
    switch(answerReady)
    {
        case 0:
            Wire.write(0);
        break;
        case 1:
            Wire.write(outAns[0]);
        break;
        case 2:
            Wire.write(outAns[0]);
            Wire.write(outAns[1]);
        break;
        case 3:
            Wire.write(outAns[0]);
            Wire.write(outAns[1]);
            Wire.write(outAns[2]);
        break;
        case 4:
            Wire.write(outAns[0]);
            for(btc i=0; i<4;i++)
                Wire.write(transData[i]);
        break;
    }
    answerReady = 0;
}

void getterEvent()
{
//поступление данных от ESP (1, 2, 5 байт)
    if(Wire.available() && !inQest[0])
    {

        inQest[0] = Wire.read();      
        switch(inQest[0] >> 4)
        {
            case 1:
            case 6:
            case 7:
                if(Wire.available())
                    inQest[1] = Wire.read();
            break;
            case 4:
                for(btc i=0; i<4 && Wire.available();i++)
                        transData[i] = Wire.read();

            break;
        }
    }
    i2cIncomingCheck();
}

transPorter::transPorter(btc addrIn)
{
    Wire.onRequest(senderEvent);
    Wire.onReceive(getterEvent);
    Wire.begin(addrIn);
    eventCount = 0;
    
    inQest[0] = 0;
    inQest[1] = 0;

    outAns[0] = 0;
    outAns[1] = 0;
    outAns[2] = 0;
}

btc transPorter::addEvent(bti ev)
{
    if(eventCount > 14)
        return 255;
    events[eventCount] = ev;
    eventCount++;
    return eventCount;
}

btc transPorter::countEvents()
{
    return eventCount;
}

btc *transPorter::question()
{
    return inQest;
}

btc *transPorter::answer()
{
    return outAns;
}

void transPorter::create(btc *trIn)
{
    transData = trIn;
}

bool transPorter::isReady(btc rd)
{
    if(answerReady)
        return false;
    answerReady = rd;
    return true;
}

bool transPorter::sendEvent()
{
    if(!eventCount)
        return false;

    outAns[0] = events[0] >> 8;
    outAns[1] = events[0] & 255;

    for(btc i=0; i<15; i++)
        events[i] = events[i+1];

    eventCount--;

    return isReady(2);
}

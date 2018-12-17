#include <Wire.h>
#include "transporter.h"

btc eventCount;
btc answerReady;
bti events[16];

btc *inData, *outData;
btc inQest[2];
btc outQest[3];

void senderEvent()
{
    switch(answerReady)
    {
        case 0:
            Wire.write(0);
        break;
        case 1:
            Wire.write(outQest[0]);
        break;
        case 2:
            Wire.write(outQest[0]);
            Wire.write(outQest[1]);
        break;
        case 3:
            Wire.write(outQest[0]);
            Wire.write(outQest[1]);
            Wire.write(outQest[2]);
        break;
        case 4:
            Wire.write(outQest[0]);
            for(btc i=0; i<4;i++)
                Wire.write(outData[i]);
    }
}

void getterEvent()
{//поступление данных от ESP (1, 2, 5 байт)
    if(Wire.available())
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
            for(btc i=0; i<4;i++)
                if(Wire.available())
                    inData[i] = Wire.read();
        break;
    }
     
}

transPorter::transPorter(btc addr)
{
    Wire.begin(addr);
    Wire.onRequest(senderEvent);
    Wire.onReceive(getterEvent);
    eventCount = 0;
    
    inQest[0] = 0;
    inQest[1] = 0;

    outQest[0] = 0;
    outQest[1] = 0;
    outQest[2] = 0;
}

btc transPorter::addEvent(bti ev)
{
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
    return outQest;
}

void transPorter::create(btc *in, btc *out)
{
    inData = in;
    outData = out;
}

void transPorter::isReady(btc rd)
{
    answerReady = rd;
}

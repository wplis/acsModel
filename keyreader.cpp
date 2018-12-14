#include <arduino.h>
#include <SPI.h>

#include "keyreader.h"

keyReader::keyReader(bool panels=true)
{
    twoPanels=panels;
}

btc keyReader::create(btc kid)
{
    id=kid;
    switch(id)
    {
        case 2:
            //rfids
            rfidEx = new RFID(7, 10);
            rfidEx->init();
            if(twoPanels)
            {
                rfidIn = new RFID(8, 10);
                rfidIn->init();
            }
        break;
        default:
            return 255;
    }
    return id;
}

btc keyReader::watchKey()
{
    bti rdBytes;
    btc j;
    i=0;

    switch(id)
    {
        case 2:
            if(rfidEx->isCard())
                if(rfidEx->readCardSerial())
                    i=1;
            if(twoPanels)
                if(rfidIn->isCard())
                    if(rfidIn->readCardSerial())
                        i+=2;
        break;
        default:
            return 255;
    }
    return i;
}

btc *keyReader::DataKey(bool secondKey=false)
{
    switch(id)
    {
        case 2:
            if(twoPanels && secondKey)
                return rfidIn->serNum;
            else
                return rfidEx->serNum;
        break;
    }
}

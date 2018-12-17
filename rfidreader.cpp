#include "rfidreader.h"

rfidReader::rfidReader()
{
}

void rfidReader::create(bool panels)
{
    twoPanels = panels;

    SPI.begin();
    riderEx = new MFRC522(7, 10);
    riderEx->PCD_Init();
    if(twoPanels)
    {
        riderIn = new MFRC522(8, 10);
        riderIn->PCD_Init();
    }
}

btc rfidReader::watchKey()
{
    i = 0;
    
    if(riderEx->PICC_IsNewCardPresent())
        if(riderEx->PICC_ReadCardSerial())
            i += 1;
        else
            i += 2;//0-нет карты 1-есть карта 2-неможем прочитать

    i = i << 4;
    
    if(twoPanels)
    {
        if(riderIn->PICC_IsNewCardPresent())
            if(riderIn->PICC_ReadCardSerial())
                i += 1;
            else
                i += 2;//то же самое только во втором полубайте 
    }
    
    return i;
}

btc *rfidReader::dataKey(bool secondKey)
{
    if(!secondKey)
        return riderEx->uid.uidByte;
    else
        if(twoPanels)
            riderIn->uid.uidByte;
        else
            return riderEx->uid.uidByte;
}

#ifndef KEYREADER_H
#define KEYREADER_H

#include <RFID.h>

#define btc unsigned char
#define bti unsigned int

class keyReader
{
private:
    btc i, id;

    bool twoPanels;
    
    RFID *rfidIn, *rfidEx;
public:
    keyReader(bool);

    btc create(btc);
    btc watchKey();
    btc *DataKey(bool);
};

#endif // KEYREADER_H

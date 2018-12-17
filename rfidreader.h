#ifndef RFIDREADER_H
#define RFIDREADER_H

#include "keyreader.h"

#include <SPI.h>
#include <require_cpp11.h>
#include <MFRC522.h>
#include <deprecated.h>
#include <MFRC522Extended.h>

class rfidReader : public keyReader
{
private:
    btc i;
    MFRC522 *riderEx, *riderIn;
public:
    rfidReader();

    void create(bool);
    btc watchKey();
    btc *dataKey(bool);
};

#endif // RFIDREADER_H

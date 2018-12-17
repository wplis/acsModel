#ifndef ACSMODEL_H
#define ACSMODEL_H

#include "accesser.h"
#include "configurator.h"
#include "rfidreader.h"
#include "transporter.h"

#define btc unsigned char
#define bti unsigned int

class acsModel
{
private:
    btc addr;
    btc id;
    btc i;
public:
    acsModel();
    
    btc create(btc);
    btc saveConfig();
    btc loadConfig();

btc configure();
    btc shId();
    btc setAddr(btc);
    btc calcPing(btc, btc, btc);
};

#endif // ACSMODEL_H

#ifndef ACSMODEL_H
#define ACSMODEL_H

#define btc unsigned char

class acsModel
{
private:
    btc addr;
    btc id;
    btc i;
    btc sensors[16];

public:
    acsModel(btc);

    btc shId();
    btc setAddr(btc);
    btc calcPing(btc, btc, btc);
    btc sensor(btc);
    btc addSensor(btc);
    btc delSensor(btc);
};

#endif // ACSMODEL_H

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#define btc unsigned char
#define bti unsigned int

class confiGurator
{
private:
    bti i;
    unsigned long waitTime, tmpTime;
    btc intensiv[6];
    btc sensors[16];
    btc trigers[16];
    btc trigWait[16];

public:
    confiGurator();

    bti sensor(btc);
    btc addSensor(btc);
    btc delSensor(btc);

    btc triger(btc, bool);
    btc addTriger(btc);
    btc delTriger(btc);

    btc intens(btc, btc);
    btc addIntens(btc);
    btc delIntens(btc);

    btc trigClic(btc, btc);

    void clickControl();
};

#endif // CONFIGURATOR_H

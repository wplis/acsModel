#ifndef ACCESSER_H
#define ACCESSER_H

#define btc unsigned char
#define bti unsigned int

struct accCode
{
public:
    accCode(bti);
    ~accCode();
    accCode *next, *prev;
    btc *keyData;
};

class accEsser
{
    btc keyCount, i;
    bti dataLen;
    accCode *top, *bot, *index;

public:
    accEsser(bti);

    btc add(btc *);
    btc count();
    btc del(btc);
    btc findKey(btc *);
};

#endif // ACCESSER_H

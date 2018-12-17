#ifndef ACCESSER_H
#define ACCESSER_H

#define btc unsigned char
#define bti unsigned int

struct accCode
{
public:
    accCode();
    accCode *next;
    btc keyData[4];
};

class accEsser
{
    btc keyCount, i;
    accCode *top, *bot, *index, *deleter;

public:
    accEsser();

    btc add(btc *);
    btc count();
    btc del(btc);
    btc findKey(btc *);
};

#endif // ACCESSER_H

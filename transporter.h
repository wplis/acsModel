#ifndef TRANSPORTER_H
#define TRANSPORTER_H

#define btc unsigned char
#define bti unsigned int
    
class transPorter
{
public:
    transPorter(btc);
    btc addEvent(bti);
    btc countEvents();

    void create(btc *, btc *);
    btc *question();
    btc *answer();

    void isReady(btc);
};

#endif // TRANSPORTER_H

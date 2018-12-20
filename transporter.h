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

    void create(btc *);
    btc *question();
    btc *answer();

    bool isReady(btc);
    bool sendEvent();
};

#endif // TRANSPORTER_H

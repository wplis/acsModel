#ifndef KEYREADER_H
#define KEYREADER_H

#define btc unsigned char

class keyReader
{
protected:
    bool twoPanels;
public:
    keyReader()
    {
    }

    virtual void create(bool);
    virtual btc watchKey();
    virtual btc *dataKey(bool);
};

#endif // KEYREADER_H

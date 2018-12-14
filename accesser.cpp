#include "accesser.h"

accCode::accCode(bti len)
{
    keyData = new btc[len];
    for(btc i=0; i<len;i++)
        keyData[i]=0;
}

accCode::~accCode()
{
    delete [] keyData;
}

accEsser::accEsser(bti dLen)
{
    dataLen = dLen;
    index = new accCode(dataLen);
    keyCount = 0;

    top = index;
    bot = index;
    index->next = index;
    index->prev = index;
}

btc accEsser::add(btc *data)
{
    if(keyCount>=254)
        return 255;

    top->next = new accCode(dataLen);
    keyCount++;
    top->next->prev = top;
    top = top->next;

    for(i=0; i<dataLen; i++)
        top->keyData[i] = data[i];

    return keyCount;
}

btc accEsser::count()
{
    return keyCount;
}

btc accEsser::del(btc number)
{
    if(!number)
        return 255;

    for(i=1, index=bot->next; i<254 && i<number; i++)
        index = index->next;

    index->prev->next = index->next;
    index->next->prev = index->prev;

    delete index;
    keyCount--;

    return i;
}

btc accEsser::findKey(btc *data)
{
    index = bot;
    bti j;
    for(i=0; i<=keyCount; i++)
    {
        for (j=0; j<dataLen; j++)
            if(index->keyData[j] != data[j])
                break;
        if(j==dataLen)
            return i;
        index = index->next;
    }
    return 255;
}

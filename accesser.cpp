#include "accesser.h"

accCode::accCode()
{
    for(btc i=0; i<4;i++)
        keyData[i]=0;
}

accEsser::accEsser()
{
    index = new accCode();
    keyCount = 0;

    top = index;
    bot = index;
    index->next = index;
}

btc accEsser::add(btc *data)
{
    if(keyCount>=254)
        return 255;

    top->next = new accCode();
    if(top->next)
    {
        keyCount++;
        top = top->next;
    }
    else
        return 255;

    for(i=0; i<4; i++)
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

    for(i=1, index=bot; i<254 && i<number; i++)
        index = index->next;

    deleter = index->next;
    index->next = index->next->next;


    delete deleter;
    keyCount--;

    return i;
}

btc accEsser::findKey(btc *data)
{
    index = bot;
    bti j;
    for(i=0; i<=keyCount; i++)
    {
        for (j=0; j<4; j++)
            if(index->keyData[j] != data[j])
                break;
        if(j==4)
            return i;
        index = index->next;
    }
    return 255;
}

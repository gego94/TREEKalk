#ifndef HEAP_H
#define HEAP_H

#include "alberobinario.h"

class heap;

ostream& operator <<(ostream& o, const heap& h);

class heap:public AlberoBinario
{
    friend ostream& operator <<(ostream& o, const heap& h);
    binary* trovaPrimaRicorrenzaHelp(double i,binary* n)const;
public:
    heap();
    heap(const heap& h,QString q);
    heap(nodo* n,const QString& q);
    ~heap();
    bool operator ==(const heap& h)const;                           // operator == profondo
    bool operator !=(const heap& h)const;                           // operator != profondo
    heap& operator =(const heap& h);                                // operator = profondo
    virtual void heapify(binary* b)=0;
    virtual void heapifyUp(binary* b)=0;
    QString converti(int i)const;
    binary* ultimo()const;
    binary* trovaPrimaRicorrenza(double i)const;
};

inline ostream& operator <<(ostream& o,const heap& h)
{
    if(h.getRadice())
        o << *(h.getRadice()) << endl ;
    else
        o << "()";
    return o;
}


#endif // HEAP_H

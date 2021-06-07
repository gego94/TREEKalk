#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "heap.h"

class maxHeap;

ostream& operator <<(ostream& o, const maxHeap& h);

class maxHeap:public heap
{
    friend ostream& operator <<(ostream& o, const maxHeap& h);
    void minimoHelp(binary* n,double& min)const;
    binary* operazioneHelp(nodo* n1,nodo* n2,char tipo)const;
public:
    maxHeap();
    maxHeap(const maxHeap& h,QString q);
    maxHeap(nodo* n,const QString& q);
    ~maxHeap();
    bool operator ==(const maxHeap& h)const;                           // operator == profondo
    bool operator !=(const maxHeap& h)const;                           // operator != profondo
    maxHeap& operator =(const maxHeap& h);                             // operator = profondo
    void heapify(binary* b);
    void heapifyUp(binary* b);

    void insert(double i);                // inserisce i nell'albero
    void cancella(nodo* n);               // cancella il nodo specifico dall'albero
    void cancella(double i);              // cancella la prima ricorrenza di i in ordine prefisso
    bool search(double i)const;           // ritorna true se trova i nell'albero
    maxHeap* copy();                       // ritorna una copia dell'albero
    void modifica(nodo* n,double info);   // modifica l'info di un nodo dell'albero
    double minimo()const;                 // ritorna il minimo dell'albero
    double massimo()const;                // ritorna il massimo dell'albero
    QString ordina()const;

    maxHeap* operazione(Albero* a,char tipo)const;
    maxHeap* intersezione(Albero* a)const;
    maxHeap* unione(Albero* a)const;
    maxHeap* operator+(Albero* a)const;
    maxHeap* operator-(Albero* a)const;
    maxHeap* operator*(Albero* a)const;
    maxHeap* operator/(Albero* a)const;
};

inline ostream& operator <<(ostream& o,const maxHeap& h)
{
    if(h.getRadice())
        o << *(h.getRadice()) << endl ;
    else
        o << "()";
    return o;
}



#endif // MAXHEAP_H

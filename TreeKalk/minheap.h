#ifndef MINHEAP_H
#define MINHEAP_H

#include "heap.h"

class minHeap;

ostream& operator <<(ostream& o, const minHeap& h);

class minHeap:public heap
{
    friend ostream& operator <<(ostream& o, const minHeap& h);
    void massimoHelp(binary* n,double& max)const;
    binary* operazioneHelp(nodo* n1,nodo* n2,char tipo)const;
public:
    minHeap();
    minHeap(const minHeap& h,QString q);
    minHeap(nodo* n,const QString& q);
    ~minHeap();
    bool operator ==(const minHeap& h)const;                           // operator == profondo
    bool operator !=(const minHeap& h)const;                           // operator != profondo
    minHeap& operator =(const minHeap& h);                             // operator = profondo
    void heapify(binary* b);
    void heapifyUp(binary* b);
    void insert(double i);                // inserisce i nell'albero
    void cancella(nodo* n);               // cancella il nodo specifico dall'albero
    void cancella(double i);              // cancella la prima ricorrenza di i in ordine prefisso
    bool search(double i)const;           // ritorna true se trova i nell'albero
    minHeap* copy();                       // ritorna una copia dell'albero
    void modifica(nodo* n,double info);   // modifica l'info di un nodo dell'albero
    double minimo()const;                 // ritorna il minimo dell'albero
    double massimo()const;                // ritorna il massimo dell'albero
    QString ordina()const;

    minHeap* operazione(Albero* a,char tipo)const;
    minHeap* intersezione(Albero* a)const;
    minHeap* unione(Albero* a)const;
    minHeap* operator+(Albero* a)const;
    minHeap* operator-(Albero* a)const;
    minHeap* operator*(Albero* a)const;
    minHeap* operator/(Albero* a)const;
};

inline ostream& operator <<(ostream& o,const minHeap& h)
{
    if(h.getRadice())
        o << *(h.getRadice()) << endl ;
    else
        o << "()";
    return o;
}



#endif // MINHEAP_H

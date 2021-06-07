#ifndef RBNODO_H
#define RBNODO_H

#include "binary.h"

class rbNodo;

ostream& operator<<(ostream& o,const rbNodo& n);

enum colore{rosso,nero,dn};

class rbNodo:public binary
{
    friend ostream& operator<<(ostream& o,const rbNodo& n);
    rbNodo* copyHelp(rbNodo* n, rbNodo* p);
    colore col;
public:
    // costruttori
    rbNodo();                                               // costruttore standard
    rbNodo(double i,rbNodo* p,rbNodo* l,rbNodo* r,colore c);         // costruttore da parametri
    rbNodo(const rbNodo& b);                                // costruttore di copia
    // metodi getter
    rbNodo* left()const;                // metodo che ritorna il figlio sinistro del nodo
    rbNodo* right()const;               // metodo che ritorna il figlio destro del nodo
    rbNodo* getPadre()const;                    // metodo che ritorna il padre destro del nodo
    colore getColore()const;
    rbNodo* getNonno()const;
    rbNodo* getZio()const;
    rbNodo* getFratello()const;

    // metodi setter
    void setLeft(rbNodo* n);            // metodo che permette di settare il figlio sinistro
    void setRight(rbNodo* n);           // metodo che permette di settare il figlio destro
    void setColore(colore c);
    // operatori
    ~rbNodo();
    bool operator ==(const rbNodo& b)const;     // operator == non profondo
    bool operator !=(const rbNodo& b)const;     // operator != non profondo
    rbNodo& operator =(const rbNodo& b);        // assegnazione non profonda
    rbNodo& operator =(double i);               // assegnazione con singolo parametro double
    // funzioni ausialiarie
    rbNodo* copy();
};

inline ostream& operator <<(ostream& o,const rbNodo& n)
{
    if(&n)
    {
        if(n.col==0)
            o << "(" << n.getInfo()<<"R";
        else
            o << "(" << n.getInfo()<<"N";
        if(n.left())
            o << *(n.left());
        o << ",";
        if(n.right())
            o << *(n.right());
        o << ")";
    }
    else
        o << "()";
    return o;
}


#endif // RBNODO_H

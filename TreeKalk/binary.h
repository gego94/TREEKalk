#ifndef BIN_H
#define BIN_H

#include "nodo.h"

class binary;

ostream& operator<<(ostream& o,const binary& n);



class binary:public nodo
{
    friend ostream& operator<<(ostream& o,const binary& n);
    binary* copyHelp(binary* n, binary* p);
public:
    // costruttori
    binary();                                               // costruttore standard
    binary(double i,binary* p,binary* l,binary* r);         // costruttore da parametri
    binary(const binary& b);                                // costruttore di copia
    // metodi getter
    virtual binary* left()const;                // metodo che ritorna il figlio sinistro del nodo
    virtual binary* right()const;               // metodo che ritorna il figlio destro del nodo
    binary* getPadre()const;                    // metodo che ritorna il padre destro del nodo
    // metodi setter
    virtual void setLeft(binary* n);            // metodo che permette di settare il figlio sinistro
    virtual void setRight(binary* n);           // metodo che permette di settare il figlio destro
    // operatori
    ~binary();
    bool operator ==(const binary& b)const;     // operator == non profondo
    bool operator !=(const binary& b)const;     // operator != non profondo
    binary& operator =(const binary& b);        // assegnazione non profonda
    binary& operator =(double i);               // assegnazione con singolo parametro double
    binary* successore()const;
    // funzioni ausialiarie
    binary* copy();                             // ritorna una copia del sottoalbero radicato in this
};

inline ostream& operator <<(ostream& o,const binary& n)
{
    if(&n)
    {
        o << "(" << n.getInfo();
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


inline QString stampa(binary *b)
{
    QString o="";
    if(b)
        o = o + QString("(") + QString::number(b->getInfo()) + stampa(b->left()) + QString(",")
                + stampa(b->right()) + QString(")");
    else
        return QString("()");
    return o;
}

#endif // BIN_H

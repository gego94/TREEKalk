#ifndef BST_H
#define BST_H

#include "binary.h"

#include <vector>


using std::vector;

class bst;
ostream& operator<<(ostream& o,const bst& n);

class bst: public binary
{
    friend ostream& operator<<(ostream& o,const bst& n);
    bst* copyHelp(nodo* n, nodo* p);
public:
    // costruttori
    bst();                                      // costruttore standard
    bst(double i,bst* p,bst* l,bst* r);         // costruttore da parametri
    bst(bst& b);                                // costruttore di copia
    /*bst(vector<double>& el)
    {
        // insert funziona NON TOCCARE PIU
        auto it=el.begin();
        bst* temp = NULL;
        for(;it!=el.end();it++)
            if(it==el.begin())
                temp=insert(*it,temp,0);
            else
                insert(*it,temp,0);
        if(temp)
            *this=*temp;

    }*/
    // funzioni ausiliarie
    bst* copy();                                       // copia il sottoalbero radicato in n
    bst* left()const;                                       // ritorna il figlio sinistro del nodo
    bst* right()const;                                      // ritorna il figlio destro
    bst* getPadre()const;
    void setLeft(bst* n);                                   // permette di settare il figlio sinistro
    void setRight(bst* n);                                  // permette di settare il figlio destro
    // operatori
    ~bst();
    bool operator ==(const bst& b);                         // operator == non profondo
    bool operator !=(const bst& b);                         // operator != non profondo
    bst& operator =(bst& b);                                // assegnazione non profonda
    bst& operator =(double i);                              // assegnazione con singolo parametro T
    bst* minimo()const;                                     // ritorna il minimo
    bst* massimo()const;                                    // ritorna il minimo
};

inline ostream& operator <<(ostream& o, const bst& n)
{
    if(&n)
    {
        o << "(" << n.getInfo() ;
        if(n.left())
            o << *n.left();
        o << ",";
        if(n.right())
            o << *n.right();
        o << ")";
    }
    else
        o << "()";
    return o;
}
#endif // BST_H

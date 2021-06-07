#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "alberobinario.h"

class BinarySearchTree;

ostream& operator <<(ostream& o, const BinarySearchTree& b);

class BinarySearchTree:public AlberoBinario
{
    friend ostream& operator <<(ostream& o, const BinarySearchTree& b);
    void ordinaHelp(binary* n,QString& q)const;
    binary* operazioneHelp(nodo* n1,nodo* n2,char tipo)const;
    bool alberiUgualiHelp(nodo* n1,nodo* n2)const;
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& b,QString q="");
    BinarySearchTree(const vector<double>& el);
    BinarySearchTree(nodo* n,const QString& q="");
    ~BinarySearchTree();
    // funzioni virtuali
    void insert(double i);                      // inserisci i nell'abr
    void cancella(nodo* n);                     // cancella il nodo n dall'abr
    void cancella(double i);                    // cancella la prima ricorrenza di i in ordine prefisso
    bool search(double i)const;                 // ritorna true se i è contenuto nell'albero
    BinarySearchTree* copy();                   // ritorna una copia dell'albero
    void modifica(nodo* n,double info);         // modifica un elemento dell'albero
    double minimo()const;                       // ritorna il minimo dell'albero
    binary* minimo(nodo* n)const;               // ritorna il minimo nel sottoalbero radicato in n
    double massimo()const;                      // ritorna il massimo dell'albero
    binary* massimo(nodo* n)const;              // ritorna il massimo nel sottoalbero radicato in n
    QString ordina()const;
    bool alberiUguali(Albero* a)const;

    BinarySearchTree* operazione(Albero* a,char tipo)const;
    BinarySearchTree* intersezione(Albero* a)const;
    BinarySearchTree* unione(Albero* a)const;
    BinarySearchTree* operator+(Albero* a)const;
    BinarySearchTree* operator-(Albero* a)const;
    BinarySearchTree* operator*(Albero* a)const;
    BinarySearchTree* operator/(Albero* a)const;
};

inline ostream& operator <<(ostream& o,const BinarySearchTree& b)
{
    if(b.getRadice())
        o << *(b.getRadice()) << endl;
    else
        o << "()" << endl;
    return o;
}


#endif // BINARYSEARCHTREE_H

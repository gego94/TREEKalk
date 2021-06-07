#ifndef rbTree_H
#define rbTree_H

#include "rbnodo.h"
#include "binarysearchtree.h"

class rbTree;


static inline bool isFogliaRb(rbNodo* n)
{
    return !n || (!n->left() && !n->right());
}

ostream& operator <<(ostream& o, const rbTree& b);

class rbTree:public BinarySearchTree
{

    friend ostream& operator <<(ostream& o, const rbTree& b);
    void ordinaHelp(binary* n,QString& q)const;
    rbNodo* operazioneHelp(nodo* n1,nodo* n2,char tipo)const;
public:
    rbTree();
    rbTree(const rbTree& b,QString q="");
    rbTree(const vector<double>& el);
    rbTree(nodo* n,const QString& q="");
    ~rbTree();
    // funzioni virtuali
    void insert(rbNodo* n);
    void insert(double i);                      // inserisci i nell'abr
    void cancella(nodo* n);                     // cancella il nodo n dall'abr
    void cancella(double i);                    // cancella la prima ricorrenza di i in ordine prefisso
    bool search(double i)const;                 // ritorna true se i è contenuto nell'albero
    rbTree* copy();                             // ritorna una copia dell'albero
    void modifica(nodo* n,double info);         // modifica un elemento dell'albero
    double minimo()const;                       // ritorna il minimo dell'albero
    binary* minimo(nodo* n)const;               // ritorna il minimo nel sottoalbero radicato in n
    double massimo()const;                      // ritorna il massimo dell'albero
    binary* massimo(nodo* n)const;              // ritorna il massimo nel sottoalbero radicato in n
    QString ordina()const;
    rbNodo* getRadice()const;
    void ruotaSx(rbNodo* n);
    void ruotaDx(rbNodo* n);
    void insert1(rbNodo* n);
    void insert2(rbNodo* n);
    void insert3(rbNodo* n);
    void insert4(rbNodo* n);
    void insert5(rbNodo* n);

    void delete1(rbNodo* n);
    void delete2(rbNodo* n);
    void delete3(rbNodo* n);
    void delete4(rbNodo* n);
    void delete5(rbNodo* n);
    void delete6(rbNodo* n);

    void staccaMinimo(rbNodo* n);

    rbTree* operazione(Albero* a,char tipo)const;
    rbTree* intersezione(Albero* a)const;
    rbTree* unione(Albero* a)const;
    rbTree* operator+(Albero* a)const;
    rbTree* operator-(Albero* a)const;
    rbTree* operator*(Albero* a)const;
    rbTree* operator/(Albero* a)const;
};


inline ostream& operator <<(ostream& o,const rbTree& b)
{
    if(b.getRadice())
        o << *(b.getRadice()) << endl;
    else
        o << "()" << endl;
    return o;
}

#endif // rbTree_H

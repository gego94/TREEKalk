#ifndef NODO_H
#define NODO_H

#include <typeinfo>
#include <iostream>
#include <list>
#include <QString>
#include <sstream>
#include <vector>

using std::ostream;
using std::list;
using std::vector;
using std::cout;
using std::endl;

class nodo;

ostream& operator<<(ostream& o,const nodo& n);
/*
class str
{
public:
    int numFigli;
    T info;
    str(int n,T i):numFigli(n),info(i){}
};
*/


class nodo
{
    friend ostream& operator<< (ostream& o,const nodo& n);

    double info;
    nodo* padre;
    list<nodo*> nodi;
    nodo* copyHelp(nodo* n, nodo* p);
public:

    // costruttori
    nodo();
    nodo(const nodo& i);                        // costruttore di copia di nodo
    nodo(int num);                              // costruttore che inizializza il nodo con num figli
    nodo(double i,nodo* p,list<nodo*>& n);      // costruttore con info, padre e figli
    nodo(double i,nodo* p);                     // costruttore con padre e info
    /*nodo(const str s[])                       // costruttore di copia che utilizza build per costruire da array
    {
        *this=*(build(s,0,NULL,0));
    }*/

    // metodi getter
    virtual nodo* getPadre()const;              // ritorna il padre
    double getInfo()const;                      // ritorna l'info del nodo
    int numeroFigli()const;                     // ritorna il numero di figli del nodo

    // metodi setter
    void setPadre(nodo* n);                     // metodo per settare il padre del nodo
    void setInfo(double i);                     // metodo per settare info
    void setFiglio(unsigned int j,nodo* n);     // permette di settare il figlio iesimo
    void aggiungiNodo(nodo* n);                 // permette di aggiungere un figlio al nodo

    // operatori
    nodo* operator[](unsigned int i)const;
    virtual ~nodo();                             // distruttore di nodo
    bool operator==(const nodo& n)const;        // operator== per singolo nodo
    bool operator!=(const nodo& n)const;        // operator!= per singolo nodo
    nodo& operator =(const nodo& n);            // operator= per copia profonda
    nodo& operator =(double n);                 // operator= per copiare l'info di n
    bool equals(nodo* n)const;                  // operator== profondo

    // metodi ausiliari
    virtual nodo* copy();                       // ritorna una copia del sottoalbero radicato in this
    /*virtual nodo* build(const str s[] ,int n, nodo* pad,int figliPadre)    // costruisce un albero partendo da un array
    {
        nodo* temp=new nodo();
        temp->info=s[0].info;
        temp->padre=pad;
        if(pad)                                             // non sono nella radice
            for(int i=0;i<s[0].numFigli;i++)
            {
                auto sum=&s[0]+figliPadre-n+i;              // inizializzo la somma con il numero di fratelli destri da saltare
                for(int j=0;j<n;j++)                       // sommo alla somma i figli dei fratelli sinistri da saltare
                    sum+=(&s[0]-1-j)->numFigli;
                temp->nodi.push_back(build(sum,i,temp,s[0].numFigli));
            }
        else                                                                    // inizializzo la radice
            for(int i=0;i<s[0].numFigli;i++)
                temp->nodi.push_back(build(&s[0]+i+1,i,temp,s[0].numFigli));

        return temp;
    }*/
    bool contenuto(double i)const;              // controlla se i è contenuto nel sottoalbero radicato in this
    bool contenuto(nodo* n)const;               // controlla se n è contenuto nel sottoalbero radicato in this
    int profondita()const;                      // ritorna la profondità dell'albero
    bool isFoglia()const;                       // ritorna true se il nodo è foglia
    int nodiLiv(int liv)const;                  // ritorna il numero di nodi a livello liv(partendo da 0)
    void distruggi();
    std::string indirizzo()const;
    nodo* trovaNodo(QString n);
    void stacca();
    nodo* getNodo(unsigned int i)const;         // ritorna il nodo iesimo se esiste
};

inline ostream& operator <<(ostream& o,const nodo& n)
{
    if(&n!=NULL)
    {
        o << "(" << n.info<<","  ;
        list<nodo*>::const_iterator i=n.nodi.begin();
        for(;i!=n.nodi.end() ;i++)
            o << **i ;
        o << ")";
    }
    else
        o << "()";
    return o;
}
#endif

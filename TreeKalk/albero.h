#ifndef ALBERO_H
#define ALBERO_H

#include "nodo.h"

class Albero;

ostream& operator <<(ostream& o,const Albero& a);

class Albero
{
    friend ostream& operator <<(ostream& o,const Albero& a);
    nodo* root;
    QString nome,tipo;
    virtual bool alberiUgualiHelp(nodo* n1,nodo* n2)const;
    virtual nodo* operazioneHelp(nodo* n1,nodo* n2,char tipo)const=0;
public:
    // costruttori
    Albero();
    Albero(nodo* n,QString q="");
    Albero(const Albero& a,const QString& q="");
    // funzioni virtuali
    virtual void insert(double i)=0;                // inserisce i nell'albero
    virtual void cancella(nodo* n)=0;               // cancella il nodo specifico dall'albero
    virtual void cancella(double i)=0;              // cancella la prima ricorrenza di i in ordine prefisso
    virtual bool search(double i)const=0;           // ritorna true se trova i nell'albero
    virtual Albero* copy()=0;                       // ritorna una copia dell'albero
    virtual void modifica(nodo* n,double info)=0;   // modifica l'info di un nodo dell'albero
    virtual double minimo()const=0;                 // ritorna il minimo dell'albero
    virtual double massimo()const=0;                // ritorna il massimo dell'albero
    virtual QString ordina()const=0;                // ordina l'albero
    QString getTipo()const;
    // metodi setter
    void setRoot(nodo* n);                          // permette di settare la radice dell'albero
    void setNome(QString n);
    void setTipo(QString t);
    // operatori
    virtual ~Albero();
    bool operator ==(const Albero& a)const;         // confronta ogni info dei nodi dei 2 alberi
    bool operator !=(const Albero& a)const;         // confronta ogni info dei nodi dei 2 alberi
    Albero& operator =(const Albero& a);            // operator= profondo
    // funzioni ausiliarie
    int nodiLiv(int l)const;                        // ritorna il numero di nodi a profondità l
    int profondita()const;                          // ritorna la profondità dell'albero
    bool contenuto(nodo* n)const;                   // ritorna true se il nodo n fa parte dell'albero
    bool contenuto(double i)const;                  // controlla se n è contenuto nell'albero
    int livelloNodo(const nodo& n)const;            // ritorna la profondità del nodo n qualora sia contenuto nell'albero
    int dimensione(nodo *n)const;
    virtual nodo* getRadice()const;
    QString getNome()const;
    nodo* trovaNodo(QString n);                     // cerca un nodo all'interno dell'albero partendo dalla stringa con indirizzo
    virtual bool alberiUguali(Albero* a)const;
    virtual Albero* operazione(Albero* a,char tipo)const=0;
    virtual Albero* unione(Albero* a)const=0;
    virtual Albero* intersezione(Albero* a)const=0;
    virtual Albero* operator+(Albero* a)const=0;
    virtual Albero* operator-(Albero* a)const=0;
    virtual Albero* operator*(Albero* a)const=0;
    virtual Albero* operator/(Albero* a)const=0;
    void getDati(nodo* n, vector<double>& d)const;
};

inline ostream& operator <<(ostream& o,const Albero& a)
{
    if(a.getRadice())
        o << *(a.root);
    else
        o << "()"<<endl;
    return o;
}


#endif // ALBERO_H

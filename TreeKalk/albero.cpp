

#include "albero.h"

Albero::Albero():root(NULL),nome("")
{}
Albero::Albero(nodo* n,QString q):nome(q),root((n)?n->copy():NULL)
{
}
Albero::Albero(const Albero& a,const QString& q):root(a.root->copy()),nome(q)
{}

Albero::~Albero()
{
    //cout << "~albero()\n" ;
    if(root!=NULL)
        delete root;
}
bool Albero::operator ==(const Albero& a)const
{
    return root->equals(a.root);
}
bool Albero::operator !=(const Albero& a)const
{
    return !(root->equals(a.root));
}
Albero& Albero::operator =(const Albero& a)
{
    if(this!=&a)
    {
        if(root)
            delete root;
        root=a.root->copy();
    }
    return *this;
}
int Albero::nodiLiv(int l)const    // ritorna il numero di nodi a profondità l          TESTARE
{
    return root->nodiLiv(l);
}
int Albero::profondita()const   // ritorna la profondità dell'albero    TESTARE
{
    if(!root)
        return 0;
    else
        return root->profondita();
}
bool Albero::contenuto(nodo* n)const       // controlla se n è contenuto nell'albero  TESTARE
{
    return root->contenuto(n);
}
bool Albero::contenuto(double i)const       // controlla se n è contenuto nell'albero  TESTARE
{
    return root->contenuto(i);
}
int Albero::livelloNodo(const nodo& n)const   // ritorna la profondità del nodo n qualora sia contenuto nell'albero
{
    if(!contenuto(const_cast<nodo*>(&n)))
        return -1;
    int p=0;
    nodo pad=n;
    while(pad.getPadre())
    {
        pad=*(pad.getPadre());
        p++;
    }
    return p;
}
nodo* Albero::getRadice()const
{
    return root;
}
void Albero::setRoot(nodo* n)
{
    root=n;
}
QString Albero::getNome()const
{
    return nome;
}

nodo* Albero::trovaNodo(QString n)
{
    if(root!=NULL)
        return root->trovaNodo(n);
    return NULL;
}
int Albero::dimensione(nodo *n)const
{
    if(!n)
        return 0;
    if(n->isFoglia())
        return 1;

    int sum=1;
    int i=n->numeroFigli();
    for(int j=0;j<i;j++)
        sum+=dimensione((*n)[j]);
    return sum;
}
bool Albero::alberiUgualiHelp(nodo* n1,nodo* n2)const
{
    if((!n1 && n2) || ( n1 && !n2 ) || ( n1->numeroFigli()!=n2->numeroFigli() ))
        return false;
    if(n1->numeroFigli()==0 && n2->numeroFigli()==0)
        return true;
    bool ris=true;
    for(int i=0;i<n1->numeroFigli() && ris;i++)
        if(n1->getNodo(i) && n2->getNodo(i))
            ris=alberiUgualiHelp(n1->getNodo(i),n2->getNodo(i));
    return ris;
}
bool Albero::alberiUguali(Albero *a) const
{
    if(!root && !a->root)
        return true;
    if((!root && a->root) || (!a->root && root))
        return false;
    return alberiUgualiHelp(root,a->root);
}
void Albero::setNome(QString n)
{
    nome=n;
}
void Albero::setTipo(QString n)
{
    tipo=n;
}
QString Albero::getTipo()const
{
    return tipo;
}
void Albero::getDati(nodo* n, vector<double>& d)const
{
    if(n)
    {
        d.push_back(n->getInfo());
        for(int i=0;i<n->numeroFigli();i++)
            getDati(n->getNodo(i),d);
    }
}

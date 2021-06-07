
#include "nodo.h"



nodo::nodo()
{
    padre=NULL;
    info=double();
}
nodo::nodo(const nodo& i):info(i.info),padre(i.padre)     // costruttore di copia di nodo
{
    for(list<nodo*>::const_iterator it=i.nodi.begin();it!=i.nodi.end();it++)
        nodi.push_back((*it)->copy());
}
nodo::nodo(int num)               // costruttore che inizializza il nodo con num figli
{
    padre=NULL;
    info=double();
    for(int i=0;i<num;i++)
        nodi.push_back(NULL);
}
nodo::nodo(double i,nodo* p,list<nodo*>& n):info(i),padre(p),nodi(n)  // costruttore con info, padre e figli
{}
nodo::nodo(double i,nodo* p):info(i),padre(p){}       // costruttore con padre e info

nodo::~nodo()                             // distruttore di nodo
{
    //cout << "~nodo() cancello : " << endl;
    if(nodi.size()>0)
    {
        list<nodo*>::const_iterator it=nodi.begin();
        for(int i = 0;it!=nodi.end();it++,i++)
            if(*it)
                delete *it;
    }
}
nodo* nodo::getPadre()const    // ritorna il padre
{
    return padre;
}
double nodo::getInfo()const            // ritorna l'info del nodo
{
    return info;
}
int nodo::numeroFigli()const                  // ritorna il numero di figli di un nodo
{
    return nodi.size();
}
nodo* nodo::getNodo(unsigned int i)const    // ritorna il nodo iesimo se esiste
{
    if(!(nodi.size()) || i>=nodi.size())
        throw std::string("Nodo non esistente");
    list<nodo*>::const_iterator it=nodi.begin();
    unsigned int j=0;
    while(j<i)
    {
        j++;
        it++;
    }
    return *it;
}
void nodo::setPadre(nodo* n)       // metodo per settare il padre del nodo
{
    padre=n;
}
void nodo::setInfo(double i)    // metodo per settare info
{
    info=i;
}
void nodo::setFiglio(unsigned int j,nodo* n)    // permette di settare il figlio iesimo
{
    if(j>=nodi.size())
        throw std::string("Stai cercando di settare un figlio che non esiste");
    list<nodo*>::iterator it=nodi.begin();
    unsigned int i=0;
    while (i<j)
    {
        i++;
        it++;
    }
    /*if(*it)
        delete *it;*/
    *it=n;
}
nodo* nodo::operator[](unsigned int i)const
{
    if(i>=nodi.size())
        throw std::string("nodo non esistente");
    list<nodo*>::const_iterator it=nodi.begin();
    unsigned int j=0;
    while(j<i)
    {
        j++;
        it++;
    }
    return *it;
}
bool nodo::operator==(const nodo& n)const   // operator== per singolo nodo
{
    return info==n.info;
}
bool nodo::operator!=(const nodo& n)const
{
    return n.info!=info;
}
nodo& nodo::operator =(const nodo& n)    // operator= per copiare l'info di n
{
    if(this != &n)
    {
        info=n.info;
    }
    return *this;
}
nodo& nodo::operator =(double n)    // operator= per copiare l'info di n
{
    info=n;
    return *this;
}
bool nodo::equals(nodo* n)const    // operator== profondo
{
    if(info!=n->info || numeroFigli()!=n->numeroFigli())
        return false;
    list<nodo*>::const_iterator it=nodi.begin();
    list<nodo*>::const_iterator it1=n->nodi.begin();
    bool ris=true;
    for(;it!=nodi.end() && ris;it++,it1++)
        ris=(*it)->equals(*it1);
    return ris;
}
nodo* nodo::copyHelp(nodo* n, nodo* p)
{
    nodo* temp=new nodo();
    temp->info=n->info;

    temp->padre=p;
    list<nodo*>::const_iterator it=n->nodi.begin();
    for(;it!=n->nodi.end();it++)
        if(*it)
            temp->nodi.push_back((*it)->copy());
    return temp;
}
nodo* nodo::copy()    // ritorna una copia del sottoalbero radicato in this
{
    return copyHelp(this,0);
}
bool nodo::contenuto(double i)const       // controlla se i è contenuto nel sottoalbero radicato in this
{
    bool trovato=false;
    if(this!=NULL)
    {
        if(info==i)
            return true;
        if(nodi.size()>0)
        {
            list<nodo*>::const_iterator it=nodi.begin();
            for(;it!=nodi.end() && !trovato;it++)
                trovato=(*it)->contenuto(i);
        }
    }
    return trovato;
}
bool nodo::contenuto(nodo* n)const       // controlla se n è contenuto nel sottoalbero radicato in this
{
    bool trovato=false;
    if(this)
    {
        if(this==n)
            return true;
        if(nodi.size()>0)
        {
            list<nodo*>::const_iterator it=nodi.begin();
            for(;it!=nodi.end() && !trovato;it++)
                trovato=(*it)->contenuto(n);
        }
    }
    return trovato;
}
int nodo::profondita()const   // ritorna la profondità dell'albero
{
    int temp=0,temp1=0;
    list<nodo*>::const_iterator it=nodi.begin();
    for(;it!=nodi.end();it++)
    {
        if(*it)
            temp1=(*it)->profondita();
        if(temp1>temp)
            temp=temp1;
    }
    return temp+1;
}
void nodo::aggiungiNodo(nodo* n)
{
    nodi.push_back(n);
}
bool nodo::isFoglia()const
{
    if(nodi.size()==0)
        return true;
    list<nodo*>::const_iterator it=nodi.begin();
    for(;it!=nodi.end();it++)
        if(nodi.size() && *it!=NULL)
            return false;
    return true;
}
int nodo::nodiLiv(int liv)const
{
    if(!liv)
        return 1;
    if(liv>profondita() || nodi.size()==0)
        return 0 ;
    int sum=0;
    list<nodo*>::const_iterator it=nodi.begin();
    for(;it!=nodi.end();it++)
        if(*it)
            sum+=(*it)->nodiLiv(liv-1);
    return sum;
}

std::string nodo::indirizzo() const
{

    const void * address = static_cast<const void*>(this);
    std::ostringstream ss;
    ss << address;
    std::string s=ss.str();
    return s;
}
void nodo::distruggi()
{
    if(padre)
    {
        list<nodo*>::iterator it1=padre->nodi.begin();
        while (*it1!=this)
            it1++;
        *it1=NULL;
        padre=NULL;
    }
    delete this;
}

nodo* nodo::trovaNodo(QString n)
{
    if(indirizzo()==n.toStdString())
        return this;
    nodo* ris=NULL;
    for(list<nodo*>::const_iterator it=nodi.begin();it!=nodi.end() && ris==NULL;it++)
        if(*it)
            ris=(*it)->trovaNodo(n);
    return ris;
}
void nodo::stacca()
{
    for(list<nodo*>::iterator it=padre->nodi.begin();it!=padre->nodi.end();it++)
        if(this==*it)
        {
            *it=NULL;
            break;
        }

    padre=NULL;
    for(list<nodo*>::iterator it=nodi.begin();it!=nodi.end();it++)
        *it=NULL;
}

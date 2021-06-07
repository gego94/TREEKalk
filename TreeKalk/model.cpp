
#include "model.h"

model::model()
{
}
model::~model()
{
    list<Albero*>::iterator it=elementi.begin();
    for(;it!=elementi.end();it++)
        if(*it)
            delete *it;
}
Albero* model::trovaDaNome(QString nome)const
{
    list<Albero*>::const_iterator it=elementi.begin();
    while ((*it)->getNome()!=nome)
        it++;
    return *it;
}
bool model::inserisci(Albero *a)
{
    if( !a || contiene(a->getNome()))
        return false;
    elementi.push_back(a);
    return true;
}
bool model::inserisci(QString a,Albero* al)
{
    if(contiene(a))
        return false;
    al->setNome(a);
    elementi.push_back(al);
    return true;
}
bool model::inserisci(QString albero,QString tipo)
{
    if(elementi.size()!=0)
        for(list<Albero*>::iterator it=elementi.begin();it!=elementi.end();it++)
            if(albero==(*it)->getNome())
                return false;
    if(tipo=="BST")
    {
        elementi.push_back(new BinarySearchTree(NULL,albero));return true;
    }
    else if(tipo=="MaxHeap")
    {
        elementi.push_back(new maxHeap(NULL,albero));return true;
    }
    else if(tipo=="MinHeap")
    {
        elementi.push_back(new minHeap(NULL,albero));return true;
    }
    else if(tipo=="AlberoRB")
    {
        elementi.push_back(new rbTree(NULL,albero));return true;
    }
    return false;
}
void model::inserisciNodoInAlbero(const QString& a,double i)
{
    try{
        trovaDaNome(a)->insert(i);}
    catch(std::string s)
    {
        cout << s;
    }
}
void model::cancella(Albero* a)
{
    delete a;
}
Albero* model::getElemento(const QString& el)
{
    list<Albero*>::iterator it=elementi.begin();
    while((*it)->getNome()!=el)
        it++;
    return *it;
}
void model::rifaiHelp(binary *b,heap* h) const
{
    if(b)
    {
        h->insert(b->getInfo());
        if (b->left())
            rifaiHelp(b->left(),h);
        if(b->right())
            rifaiHelp(b->right(),h);
    }
}
heap* model::rifai(heap *h) const
{
    heap* temp;
    if(dynamic_cast<maxHeap*>(h))
        temp=new maxHeap();
    if(dynamic_cast<minHeap*>(h))
        temp=new minHeap();
    rifaiHelp(h->getRadice(),temp);
    return temp;
}
void model::cancelSlotSottoalbero(QString albero,QString nod)
{
    Albero* a = trovaDaNome(albero);
    if(dynamic_cast<rbTree*>(a))
        throw QString("Funzione non disponibile per alberi rosso neri.");
    nodo* temp=a->trovaNodo(nod);
    if(temp!=NULL)
    {
        if(temp==a->getRadice())
            a->setRoot(NULL);
        temp->distruggi();
    }
    if(dynamic_cast<heap*>(a))
    {
        heap* temp=rifai(dynamic_cast<heap*>(a));
        if(a->getRadice())
            delete a->getRadice();
        a->setRoot(temp->getRadice());
    }
}
void model::cancelSlotNodo(QString albero,QString nod)
{
    Albero* a=trovaDaNome(albero);
    nodo* temp=a->trovaNodo(nod);
    if(temp!=NULL)
        try
        {
            a->cancella(temp);
        }
    catch(QString q)
    {
        throw QString(q);
    }
}

void model::cancelSlotAlbero(QString albero)
{
    list<Albero*>::iterator it=elementi.begin();
    for(;it!=elementi.end();it++)
        if((*it)->getNome()==albero)
        {
            elementi.erase(it);
            break;
        }
}

void model::modificaNodoSlot(QString albero,QString nodo,double i)
{
    (trovaDaNome(albero))->modifica((trovaDaNome(albero))->trovaNodo(nodo),i);
}

bool model::cerca(QString albero,double i)
{
    Albero* a=trovaDaNome(albero);
    if(a)
        return a->search(i);
    return false;
}
double model::massimo(QString albero)const
{
    return trovaDaNome(albero)->massimo();
}
double model::minimo(QString albero)const
{
    return trovaDaNome(albero)->minimo();
}
QString model::order(QString albero)const
{
    Albero* a=trovaDaNome(albero);
    if(!a->getRadice())
        return "[]";
    return a->ordina();
}

Albero* model::somma(QString albero1,QString albero2)const
{
    try
    {
        Albero *a1=trovaDaNome(albero1),*a2=trovaDaNome(albero2);
        return a1->operator +(a2);
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
Albero* model::sottrai(QString albero1,QString albero2)const
{
    try
    {
        Albero *a1=trovaDaNome(albero1),*a2=trovaDaNome(albero2);
        return a1->operator -(a2);
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
Albero* model::moltiplica(QString albero1,QString albero2)const
{
    try
    {
        Albero *a1=trovaDaNome(albero1),*a2=trovaDaNome(albero2);
        return a1->operator *(a2);
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
Albero* model::dividi(QString albero1,QString albero2)const
{
    try
    {
        Albero *a1=trovaDaNome(albero1),*a2=trovaDaNome(albero2);
        return a1->operator /(a2);
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
Albero* model::unisci(QString albero1,QString albero2)const
{
    try
    {
        Albero *a1=trovaDaNome(albero1),*a2=trovaDaNome(albero2);
        return a1->unione(a2);
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
Albero* model::interseca(QString albero1,QString albero2)const
{
    try
    {
        Albero *a1=trovaDaNome(albero1),*a2=trovaDaNome(albero2);
        return a1->intersezione(a2);
    }
    catch(QString s)
    {
        throw QString(s);
    }}
bool model::contiene(QString nome) const
{
    for(list<Albero*>::const_iterator it=elementi.begin();it!=elementi.end();it++)
        if((*it)->getNome()==nome)
            return true;
    return false;
}


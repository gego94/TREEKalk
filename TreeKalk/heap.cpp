
#include "heap.h"

heap::heap():AlberoBinario(){}
heap::heap(const heap& b,QString q):AlberoBinario(b.getRadice()->copy(),q){}
heap::heap(nodo* n,const QString& q):AlberoBinario(n,q){}

heap::~heap()
{
    //cout << "~alberobinario()\n";
}

bool heap::operator ==(const heap& b)const
{
    return AlberoBinario::operator ==(b);
}
bool heap::operator !=(const heap& b)const
{
    return !(operator ==(b));
}
heap& heap::operator =(const heap& b)
{
    if(this!=&b)
    {
        delete getRadice();
        setRoot(b.getRadice()->copy());
    }
    return *this;
}
QString heap::converti(int i) const
{
    QString s=QString::number(i);
    return s.setNum(i,2);
}
binary* heap::ultimo()const
{
    QString b=converti(dimensione(getRadice()));
    binary* temp=getRadice();
    int j=1;
    while(j<b.size())
    {
        if( b.mid(j,1)=="0")
            temp=temp->left();
        else if(b.mid(j,1)=="1")
            temp=temp->right();
        j++;
    }
    return temp;
}

binary* heap::trovaPrimaRicorrenza(double i)const
{
    return trovaPrimaRicorrenzaHelp(i,getRadice());
}
binary* heap::trovaPrimaRicorrenzaHelp(double i,binary* n)const
{
    if(!n)
        return NULL;
    binary* temp=NULL;
    if(i==n->getInfo())
        return n;
    if(!temp && n->left())
        temp=trovaPrimaRicorrenzaHelp(i,n->left());
    if(!temp && n->right())
        temp=trovaPrimaRicorrenzaHelp(i,n->right());
    return temp;
}







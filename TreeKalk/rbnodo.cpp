
#include "rbnodo.h"

rbNodo::rbNodo():binary(),col(nero)                                                // costruttore standard
{}
rbNodo::rbNodo(double i,rbNodo* p,rbNodo* l,rbNodo* r,colore c):binary(i,p,l,r),col(c)       // costruttore da parametri
{}
rbNodo::rbNodo(const rbNodo& b):binary(*(const_cast<rbNodo&>(b).copy())),col(b.getColore())      // costruttore di copia
{}
rbNodo* rbNodo::left()const         // metodo che ritorna il figlio sinistro del nodo
{
    return static_cast<rbNodo*>(binary::left());
}
rbNodo* rbNodo::right()const        // metodo che ritorna il figlio destro
{
    return dynamic_cast<rbNodo*>(binary::right());
}
rbNodo* rbNodo::getPadre()const
{
    return dynamic_cast<rbNodo*>(binary::getPadre());
}
rbNodo* rbNodo::getNonno()const
{
    if(!getPadre())
        return NULL;
    return getPadre()->getPadre();
}
rbNodo* rbNodo::getZio()const
{
    if(!getPadre() || !getNonno())
        return NULL;
    if(getNonno()->left()==getPadre())
        return getNonno()->right();
    return getNonno()->left();
}
rbNodo* rbNodo::getFratello()const
{
    if(this && getPadre())
        if(getPadre()->right()==this)
            return getPadre()->left();
        else
            return getPadre()->right();
    return NULL;
}

void rbNodo::setLeft(rbNodo* n)    // metodo che permette di settare il figlio sinistro
{
    binary::setLeft(n);
}
void rbNodo::setRight(rbNodo* n)   // metodo che permette di settare il figlio destro
{
    binary::setRight(n);
}
void rbNodo::setColore(colore c)
{
    col=c;
}
rbNodo::~rbNodo()
{
    //cout << "~rbNodo()\n";
}
bool rbNodo::operator ==(const rbNodo& b)const
{
    return nodo::operator ==(dynamic_cast<const nodo&>(b));
}
bool rbNodo::operator !=(const rbNodo& b)const
{
    return !(operator ==(b));
}
rbNodo& rbNodo::operator =(const rbNodo& b)   // assegnazione profonda
{
    if(this!=&b)
    {
        setInfo(b.getInfo());
    }
    return *this;
}
rbNodo& rbNodo::operator =(double i)       // assegnazione con singolo parametro T
{
    setInfo(i);
    return *this;
}

rbNodo* rbNodo::copyHelp(rbNodo* n, rbNodo* p)
{
    rbNodo* temp=new rbNodo(n->getInfo(),p,NULL,NULL,n->getColore());
    if(n->left())
        temp->setLeft(copyHelp(n->left(),temp));
    else
        n->setLeft(NULL);

    if(n->right())
        temp->setRight(copyHelp(n->right(),temp));
    else
        n->setRight(NULL);

    return temp;
}
rbNodo* rbNodo::copy()    // copia il sottoalbero radicato in n
{
    return copyHelp(this,0);
}
colore rbNodo::getColore()const
{
    return col;
}








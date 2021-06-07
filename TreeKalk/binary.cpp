
#include "binary.h"

binary::binary():nodo(2)                                                // costruttore standard
{}
binary::binary(double i,binary* p,binary* l,binary* r):nodo(i,p)        // costruttore da parametri
{
    aggiungiNodo(l);
    aggiungiNodo(r);
}
binary::binary(const binary& b):nodo(*(const_cast<binary&>(b).copy()))      // costruttore di copia
{}
binary* binary::left()const         // metodo che ritorna il figlio sinistro del nodo
{
    return static_cast<binary*>(getNodo(0));
}
binary* binary::right()const        // metodo che ritorna il figlio destro
{
    return dynamic_cast<binary*>(getNodo(1));
}
binary* binary::getPadre()const
{
    return dynamic_cast<binary*>(nodo::getPadre());
}
void binary::setLeft(binary* n)    // metodo che permette di settare il figlio sinistro
{
    setFiglio(0,n);
}
void binary::setRight(binary* n)   // metodo che permette di settare il figlio destro
{
    setFiglio(1,n);
}
binary::~binary()
{
    //cout << "~binary()\n";
}
bool binary::operator ==(const binary& b)const
{
    return nodo::operator ==(dynamic_cast<const nodo&>(b));
}
bool binary::operator !=(const binary& b)const
{
    return !(operator ==(b));
}
binary& binary::operator =(const binary& b)   // assegnazione profonda
{
    if(this!=&b)
    {
        setInfo(b.getInfo());
    }
    return *this;
}
binary& binary::operator =(double i)       // assegnazione con singolo parametro T
{
    setInfo(i);
    return *this;
}

binary* binary::copyHelp(binary* n, binary* p)
{
    binary* temp=new binary(n->getInfo(),p,NULL,NULL);
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
binary* binary::copy()    // copia il sottoalbero radicato in n
{
    return copyHelp(this,0);
}
binary* binary::successore()const
{
    if(!this || !right())
        return NULL;
    binary* temp=right();
    while(temp->left())
        temp=temp->left();
    return temp;
}


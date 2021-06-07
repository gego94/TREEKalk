
#include "bst.h"

bst::bst():binary(0.0,NULL,NULL,NULL){}                      // costruttore standard
bst::bst(double i,bst* p,bst* l,bst* r):binary(i,p,l,r)      // costruttore da parametri
{}
bst::bst(bst& b):binary(*b.copy())                           // costruttore di copia
{}
bst::~bst()
{
    //cout << "~bst()\n";
}
bst* bst::copyHelp(nodo* n, nodo* p)
{
    bst* temp= new bst();
    temp->setInfo(n->getInfo());
    temp->setPadre(p);
    if(dynamic_cast<bst*>(n)->left())
        temp->setLeft(dynamic_cast<bst*>(dynamic_cast<bst*>(n)->left())->copy());
    else
        dynamic_cast<bst*>(n)->setLeft(NULL);

    if(dynamic_cast<bst*>(n)->right())
        temp->setRight(dynamic_cast<bst*>(dynamic_cast<bst*>(n)->right())->copy());
    else
        dynamic_cast<bst*>(n)->setRight(NULL);

    return temp;
}
bst* bst::copy()    // copia il sottoalbero radicato in n
{
    return copyHelp(this,0);
}
bst* bst::left()const         // metodo che ritorna il figlio sinistro del nodo
{
    return dynamic_cast<bst*>(binary::left());
}
bst* bst::right()const        // metodo che ritorna il figlio destro
{
    return dynamic_cast<bst*>(binary::right());
}
bst* bst::getPadre()const
{
    return dynamic_cast<bst*>(nodo::getPadre());
}
void bst::setLeft(bst* n)    // metodo che permette di settare il figlio sinistro
{
    setFiglio(0,n);
}
void bst::setRight(bst* n)    // metodo che permette di settare il figlio sinistro
{
    setFiglio(1,n);
}
bool bst::operator ==(const bst& b)
{
    return binary::operator ==(dynamic_cast<const binary&>(b));
}
bool bst::operator !=(const bst& b)
{
    return !(operator ==(b));
}
bst& bst::operator =(bst& b)   // assegnazione non profonda
{
    if(this!=&b)
    {
        /*delete this;
        *this = *b.copy();*/
        setInfo(b.getInfo());
    }
    return *this;
}
bst& bst::operator =(double i)       // assegnazione con singolo parametro T
{
    setInfo(i);
    return *this;
}
bst* bst::minimo()const
{
    if(this==NULL)
        return NULL;
    bst* temp= const_cast<bst*>(this);
    while(temp->left())
        temp=temp->left();
    return temp;
}
bst* bst::massimo()const
{
    if(this==NULL)
        return NULL;
    bst* temp= const_cast<bst*>(this);
    while(temp->right())
        temp=temp->right();
    return temp;
}

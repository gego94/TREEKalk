
#include "rbtree.h"

rbTree::rbTree():BinarySearchTree()
{setTipo(QString("RBTree"));}
rbTree::rbTree(const rbTree& b,QString q):BinarySearchTree(b.getRadice()->copy(),q)
{setTipo(QString("RBTree"));}
rbTree::rbTree(const vector<double>& el)
{
    setTipo(QString("RBTree"));
    for(unsigned int i=0;i<el.size();i++)
        insert(el[i]);
}
rbTree::rbTree(nodo* n,const QString& q):BinarySearchTree(n,q)
{setTipo(QString("RBTree"));}
rbTree::~rbTree()
{
    //cout << "~rbTree()\n";
}
rbNodo* rbTree::getRadice()const
{
    return dynamic_cast<rbNodo*>(BinarySearchTree::getRadice());
}
void rbTree::insert(rbNodo* n)
{
    rbNodo* temp=getRadice();

    if(temp==NULL)
        setRoot(new rbNodo(n->getInfo(),NULL,NULL,NULL,nero));
    else
        while(true)
            if(n->getInfo()>=temp->getInfo())
                if(!temp->right())
                {
                    temp->setRight(n);
                    temp->right()->setPadre(temp);
                    break;
                }
                else
                    temp=temp->right();
            else
                if(!temp->left())
                {
                    temp->setLeft(n);
                    temp->left()->setPadre(temp);
                    break;
                }
                else
                    temp=temp->left();
}

void rbTree::ruotaSx(rbNodo *n)
{
    if(n && n->right())
    {
        rbNodo* beta=n->right()->left(),*y=n->right();
        if(n==getRadice())
            setRoot(y);

        y->setPadre(n->getPadre());
        if(n->getPadre() && n->getPadre()->left()==n)
            n->getPadre()->setLeft(y);
        else if(n->getPadre() && n->getPadre()->right()==n)
            n->getPadre()->setRight(y);

        y->setLeft(n);
        n->setPadre(y);
        n->setRight(beta);
        if(beta)
            beta->setPadre(n);
    }
}
void rbTree::ruotaDx(rbNodo *n)
{
    if(n && n->left())
    {
        rbNodo* x=n->left(),*beta=x->right();
        if(n==getRadice())
            setRoot(x);

        x->setPadre(n->getPadre());

        if(n->getPadre() && n->getPadre()->left()==n)
            n->getPadre()->setLeft(x);
        else if(n->getPadre() && n->getPadre()->right()==n)
            n->getPadre()->setRight(x);

        x->setRight(n);
        n->setPadre(x);
        n->setLeft(beta);
        if(beta)
            beta->setPadre(n);
    }
}
void rbTree::insert5(rbNodo* n)
{
    if(n && n->getPadre()==n->getNonno()->left())
    {
        n->getPadre()->setColore(nero);
        n->getNonno()->setColore(rosso);
        if (n == n->getPadre()->left() && n->getPadre() == n->getNonno()->left())
            ruotaDx(n->getNonno());
        else
            ruotaSx(n->getNonno());
    }
    else if(n)
    {
        n->getPadre()->setColore(nero);
        n->getNonno()->setColore(rosso);
        if (n == n->getPadre()->right() && n->getPadre() == n->getNonno()->right())
            ruotaSx(n->getNonno());
        else
            ruotaDx(n->getNonno());
    }
}
void rbTree::insert4(rbNodo* n)
{
    if(n && n->getPadre() && n->getPadre()==n->getNonno()->left())
    {
        if (n == n->getPadre()->right() && n->getPadre()==n->getNonno()->left())
        {
            ruotaSx(n->getPadre());
            n = n->left();
        }
        else if (n == n->getPadre()->left() && n->getPadre()==n->getNonno()->right())
        {
            ruotaDx(n->getPadre());
            n = n->right();
        }
    }
    else if(n)
    {
        if (n == n->getPadre()->left() && n->getPadre()==n->getNonno()->right())
        {
            ruotaDx(n->getPadre());
            n = n->right();
        }
        else if (n == n->getPadre()->right() && n->getPadre()==n->getNonno()->left())
        {
            ruotaSx(n->getPadre());
            n = n->left();
        }
    }
    insert5(n);
}
void rbTree::insert3(rbNodo* n)
{
    if(n->getZio() && n->getZio()->getColore()==rosso)
    {
        dynamic_cast<rbNodo*>(n->getPadre())->setColore(nero);
        dynamic_cast<rbNodo*>(n->getZio())->setColore(nero);
        dynamic_cast<rbNodo*>(n->getNonno())->setColore(rosso);
        insert1(n->getNonno());
    }
    else
        insert4(n);
}
void rbTree::insert2(rbNodo* n)
{
    if(n->getPadre()->getColore()==rosso)
        insert3(n);
}
void rbTree::insert1(rbNodo* n)
{
    if(!n->getPadre())
        n->setColore(nero);
    else
        insert2(n);
}
void rbTree::insert(double i)
{
    rbNodo* n=new rbNodo(i,NULL,NULL,NULL,rosso);
    insert(n);
    insert1(n);
}

void rbTree::staccaMinimo(rbNodo *n)
{
    rbNodo* m=dynamic_cast<rbNodo*>(n->successore());
    //sostituisco l'info
    if(!m)
        m=n;
    n->setInfo(m->getInfo());
    // controllo se il minimo è una foglia rossa, in tal caso basta cancellarlo
    if(m && m->getColore()==rosso && m->isFoglia())
    {
        m->stacca();
        delete m;
    }// controllo se il minimo ha figlio dx ed è nero
    else if(m && ((m->right() && m->right()->getColore()==rosso) ||
                  (m->left() && m->left()->getColore()==rosso)) && m->getColore()==nero)
    {
        if(m==m->getPadre()->left())
        {
            if(m->left())
            {
                m->getPadre()->setLeft(m->left());
                m->left()->setPadre(m->getPadre());
                m->left()->setColore(nero);
            }
            else
            {
                m->getPadre()->setLeft(m->right());
                m->right()->setPadre(m->getPadre());
                m->right()->setColore(nero);
            }
        }
        else if(m==m->getPadre()->right())
        {
            if(m->left())
            {
                m->getPadre()->setRight(m->left());
                m->left()->setPadre(m->getPadre());
                m->left()->setColore(nero);
            }
            else
            {
                m->getPadre()->setRight(m->right());
                m->right()->setPadre(m->getPadre());
                m->right()->setColore(nero);
            }
        }
        m->setPadre(NULL);m->setLeft(NULL);m->setRight(NULL);
        delete m;
    }
    else if(m && m->getColore()==nero && m->isFoglia())
    {
        m->setColore(dn);
        delete1(m);
        if(m && m->getColore()==dn)
        {
            m->stacca();
            delete m;
        }
    }
}
void rbTree::delete6(rbNodo *n)
{
    cout << "delete6\n";
    if(n->getColore()==dn && n->getFratello() && n->getFratello()->getColore()==nero)
    {
        if(n->getPadre()->left()==n && n->getFratello()->right() && n->getFratello()->right()->getColore()==rosso)
        {
            ruotaSx(n->getPadre());
            n->getNonno()->right()->setColore(nero);
        }
        else if(n->getPadre()->right()==n && n->getFratello()->left() && n->getFratello()->left()->getColore()==rosso)
        {
            ruotaDx(n->getPadre());
            n->getNonno()->left()->setColore(nero);
        }
        n->getNonno()->setColore(n->getPadre()->getColore());
        n->getPadre()->setColore(nero);
        if(!n->isFoglia())
            n->setColore(nero);
    }
}
void rbTree::delete5(rbNodo *n)
{
    cout << "delete5\n";
    if(n->getColore()==dn && n->getFratello() && n->getFratello()->getColore()==nero)
    {
        if(n->getPadre()->left()==n &&
                (n->getFratello()->left() && n->getFratello()->left()->getColore()==rosso) &&
                (!(n->getFratello()->right()) || n->getFratello()->right()->getColore()==nero))
        {
            ruotaDx(n->getFratello());
            colore c=n->getFratello()->getColore();
            n->getFratello()->setColore(n->getFratello()->right()->getColore());
            n->getFratello()->right()->setColore(c);
        }
        else if(n->getPadre()->right()==n &&
                (n->getFratello()->right() && n->getFratello()->right()->getColore()==rosso) &&
                (!(n->getFratello()->left()) || n->getFratello()->left()->getColore()==nero))
        {
            ruotaSx(n->getFratello());
            colore c=n->getFratello()->getColore();
            n->getFratello()->setColore(n->getFratello()->left()->getColore());
            n->getFratello()->left()->setColore(c);
        }
    }
    delete6(n);
}
void rbTree::delete4(rbNodo *n)
{
    cout << "delete4\n";
    if(n->getColore()==dn && n->getPadre()->getColore()==rosso && n->getFratello() &&
            n->getFratello()->getColore()==nero &&
                (!(n->getFratello()->left()) || n->getFratello()->left()->getColore()==nero) &&
                (!(n->getFratello()->right()) || n->getFratello()->right()->getColore()==nero))
    {
        n->getPadre()->setColore(nero);
        n->getFratello()->setColore(rosso);
        if(!n->isFoglia())
            n->setColore(nero);
    }
    else
        delete5(n);
}
void rbTree::delete3(rbNodo *n)
{
    cout << "delete3\n";
    if(n->getColore()==dn && n->getPadre()->getColore()==nero &&
           n->getFratello() && n->getFratello()->getColore()==nero &&
            (!(n->getFratello()->left()) || n->getFratello()->left()->getColore()==nero) &&
            (!(n->getFratello()->right()) || n->getFratello()->right()->getColore()==nero))
    {
        n->getFratello()->setColore(rosso);
        n->getPadre()->setColore(dn);
        if(!n->isFoglia())
            n->setColore(nero);
        delete1(n->getPadre());
    }
    delete4(n);
}
void rbTree::delete2(rbNodo *n)
{
    cout << "delete2\n";
    if(n->getPadre()->getColore()==nero && n->getFratello() &&  n->getFratello()->getColore()==rosso &&
            (!(n->getFratello()->left()) || n->getFratello()->left()->getColore()==nero) &&
            (!(n->getFratello()->right()) || n->getFratello()->right()->getColore()==nero))
    {
        if(n->getPadre()->left()==n)
            ruotaSx(n->getPadre());
        else if(n->getPadre()->right()==n)
            ruotaDx(n->getPadre());
        colore c=n->getPadre()->getColore();
        n->getPadre()->setColore(n->getNonno()->getColore());
        n->getNonno()->setColore(c);
    }
    delete3(n);
}
void rbTree::delete1(rbNodo *n)
{
    cout << "delete1\n";
    if(getRadice()==n && n->getColore()==dn)
        n->setColore(nero);
    else if(n && n->getPadre())
        delete2(n);
}
void rbTree::cancella(nodo *n)
{
    if(n==getRadice() && n->isFoglia())
    {
        delete n;
        setRoot(NULL);
    }
    else
        staccaMinimo(dynamic_cast<rbNodo*>(n));
}
void rbTree::cancella(double i)
{
    if(!contenuto(i))
        throw QString("Informazione non contenuta nell'albero.");
    rbNodo* n=getRadice();
    while (n && n->getInfo()!=i)
    {
        if(n->getInfo()>i)
            n=n->left();
        else
            n=n->right();
    }
    if(n->getInfo()==i)
        delete n;
}

bool rbTree::search(double i)const
{
    binary* temp=getRadice();
    if(!temp)
        return false;
    while(temp)
    {
        if(temp->getInfo()==i)
            return true;
        temp=(i>=temp->getInfo())?temp->right():temp->left();
    }
    return false;
}
rbTree* rbTree::copy()
{
    return new rbTree(getRadice()->copy());
}
void rbTree::modifica(nodo* n,double info)
{
    cancella(n);
    insert(info);
}
binary* rbTree::minimo(nodo* n)const
{
    binary* temp=dynamic_cast<binary*>(n);
    while (temp->left())
        temp=temp->left();
    return temp;
}
binary* rbTree::massimo(nodo* n)const
{
    binary* temp=dynamic_cast<binary*>(n);
    while (temp->right())
        temp=temp->right();
    return temp;
}
double rbTree::minimo()const
{
    return minimo(getRadice())->getInfo();
}
double rbTree::massimo()const
{
    return massimo(getRadice())->getInfo();
}

void rbTree::ordinaHelp(binary* n,QString& q)const
{
    if(n)
    {
        if(n->left())
            ordinaHelp(n->left(),q);
        q=q+QString::number(n->getInfo())+",";
        if(n->right())
            ordinaHelp(n->right(),q);
    }
}
QString rbTree::ordina()const
{
    QString q="[";
    ordinaHelp(getRadice(),q);
    q.remove(q.size()-1,1);
    q+="]";

    return q;
}

rbNodo* rbTree::operazioneHelp(nodo* n1,nodo* n2,char tipo)const
{
    rbTree* t=new rbTree();
    vector<double> dati,dati1;
    getDati(n1,dati);
    getDati(n2,dati1);
    vector<double>::const_iterator it=dati.begin(),it1=dati1.begin();
    for(int i=0;i<dati.size();i++)
    {
        if(tipo=='+')
            t->insert((*it)+(*it1));
        else if(tipo=='-')
            t->insert((*it)-(*it1));
        else if(tipo=='*')
            t->insert((*it)*(*it1));
        else if(tipo=='/')
        {
            if(*it1==0)
            {
                delete t;
                throw QString("Operazione non valida.Divisione per 0.");
            }
            t->insert((*it)/(*it1));
        }
        else
            throw QString("Operazione non valida");
        it++;it1++;
    }
    return t->getRadice();
}

rbTree* rbTree::operazione(Albero* a,char tipo)const
{
    if(!alberiUguali(a))
        throw QString("Alberi di dimensione diversa.Impossibile eseguire l'operazione.");
    rbTree* temp=new rbTree();
    temp->setRoot(operazioneHelp(getRadice(),a->getRadice(),tipo));
    return temp;
}
rbTree* rbTree::unione(Albero* a)const
{
    vector<double> dati;
    getDati(getRadice(),dati);
    getDati(a->getRadice(),dati);
    rbTree* ris=new rbTree();
    vector<double>::const_iterator it=dati.begin();
    for(;it!=dati.end();it++)
        ris->insert(*it);
    return ris;
}
rbTree* rbTree::intersezione(Albero* a)const
{
    vector<double> dati1,dati2,dati3;
    getDati(getRadice(),dati1);
    getDati(a->getRadice(),dati2);
    for(vector<double>::const_iterator it=dati1.begin();it!=dati1.end();it++)
        if(find(dati2.begin(), dati2.end(), *it) != dati2.end())
        {
            vector<double>::iterator it1=dati2.begin();
            while(*it1!=*it)
                it1++;
            dati2.erase(it1);
            dati3.push_back(*it);
        }

    rbTree* ris=new rbTree();
    for(vector<double>::const_iterator it=dati3.begin();it!=dati3.end();it++)
        ris->insert(*it);
    return ris;
}
rbTree* rbTree::operator+(Albero* a)const
{
    return operazione(a,'+');
}
rbTree* rbTree::operator-(Albero* a)const
{
    return operazione(a,'-');
}
rbTree* rbTree::operator*(Albero* a)const
{
    return operazione(a,'*');
}
rbTree* rbTree::operator/(Albero* a)const
{
    return operazione(a,'/');
}


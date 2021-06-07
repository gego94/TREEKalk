

#include "binarysearchtree.h"

BinarySearchTree::BinarySearchTree():AlberoBinario()
{setTipo(QString("BST"));}
BinarySearchTree::BinarySearchTree(const BinarySearchTree& b,QString q):AlberoBinario(b.getRadice()->copy(),q)
{setTipo(QString("BST"));}
BinarySearchTree::BinarySearchTree(const vector<double>& el)
{
    setTipo(QString("BST"));
    for(unsigned int i=0;i<el.size();i++)
        insert(el[i]);
}
BinarySearchTree::BinarySearchTree(nodo* n,const QString& q):AlberoBinario(n,q)
{setTipo(QString("BST"));}
BinarySearchTree::~BinarySearchTree()
{
    //cout << "~binarysearchtree()\n";
}
void BinarySearchTree::insert(double i)
{
    binary* temp=getRadice();
    if(temp==NULL)
        setRoot(new binary(i,NULL,NULL,NULL));
    else
        while(true)
            if(i>=temp->getInfo())
                if(!temp->right())
                {
                    temp->setRight(new binary(i,temp,NULL,NULL));
                    break;
                }
                else
                    temp=temp->right();
            else
                if(!temp->left())
                {
                    temp->setLeft(new binary(i,temp,NULL,NULL));
                    break;
                }
                else
                    temp=temp->left();
}

void BinarySearchTree::cancella(nodo* n)
{
    if(!(contenuto(n)))
        throw new std::string("Nodo non contenuto nell'albero.");
    binary* temp=getRadice();
    if(temp==n)
    {
        if(getRadice()->isFoglia())
        {
            delete getRadice();
            setRoot(NULL);
        }
        else
        {
            if(!temp->right())
            {
                binary* t=getRadice()->left();
                getRadice()->setLeft(NULL);
                setRoot(t);
            }
            else if(!temp->left())
            {
                binary* t=getRadice()->right();
                getRadice()->setRight(NULL);
                setRoot(t);
            }
            else
            {
                setRoot(getRadice()->right());
                nodo* help=minimo(getRadice());
                dynamic_cast<binary*>(help)->setLeft(temp->left());
                dynamic_cast<binary*>(help)->left()->setPadre(help);
                temp->setLeft(NULL);
                temp->setRight(NULL);
            }
            getRadice()->setPadre(NULL);
            delete temp;
        }
    }
    else
    {
        // se temp è foglia devo aggiornare il campo left o right del padre a null e basta
        if(n->isFoglia())
        {
            if(dynamic_cast<binary*>(n->getPadre())->right()==n)
                dynamic_cast<binary*>(n->getPadre())->setRight(NULL);
            else
                dynamic_cast<binary*>(n->getPadre())->setLeft(NULL);
            delete n;
        }
        else
        {
            // salvo i dati del nodo da staccare
            binary* pad=dynamic_cast<binary*>(n->getPadre()),
                    *sx=dynamic_cast<binary*>(n)->left(),
                    *dx=dynamic_cast<binary*>(n)->right();
            // stacco il nodo
            dynamic_cast<binary*>(n)->setPadre(NULL);
            dynamic_cast<binary*>(n)->setLeft(NULL);
            dynamic_cast<binary*>(n)->setRight(NULL);
            // controllo se temp ha figlio destro o meno
            if(!dx)
            {
                // controllo se n era figlio destro o sinistro
                sx->setPadre(pad);
                // se n era figlio sinistro aggiorno il figlio sinistro del padre
                if(pad->left()==n)
                    pad->setLeft(sx);
                else
                    pad->setRight(sx);
            }
            else if(!sx)
            {
                // controllo se temp era figlio destro o sinistro
                dx->setPadre(pad);
                // se temp era figlio sinistro aggiorno il figlio sinistro del padre
                if(pad->left()==n)
                    pad->setLeft(dx);
                else
                    pad->setRight(dx);
            }
            else
            {
                dx->setPadre(pad);
                // controllo se temp era figlio destro o sinistro del padre
                if(pad->left()==n)
                    pad->setLeft(dx);
                else
                    pad->setRight(dx);
                // recupero il minimo del figlio destro e setto il suo figlio sinistro col sinistro di temp
                binary* help=minimo(dx);
                help->setLeft(sx);
                help->left()->setPadre(help);
            }
            delete n;
        }
    }
}

    void BinarySearchTree::cancella(double i)
{
    if(!(contenuto(i)))
        throw QString("Informazione non contenuta nell'albero.");

    binary* temp=getRadice();
    if(temp->getInfo()==i)
    {
        if(getRadice()->isFoglia())
        {
            delete getRadice();
            setRoot(NULL);
        }
        else
        {
            if(!temp->right())
                setRoot(getRadice()->left());
            else if(!temp->left())
                setRoot(getRadice()->right());
            else
            {
                setRoot(getRadice()->right());
                nodo* help=minimo(getRadice());
                dynamic_cast<binary*>(help)->setLeft(temp->left());
                dynamic_cast<binary*>(help)->left()->setPadre(help);
            }
            getRadice()->setPadre(NULL);
            temp->setLeft(NULL);
            temp->setRight(NULL);
            delete temp;
        }
    }
    else
    {
        while (temp->getInfo()!=i)
            temp=(i>=temp->getInfo())?temp->right():temp->left();
        // se temp è foglia devo aggiornare il campo left o right del padre a null e basta
        if(temp->isFoglia())
        {
            if(temp->getPadre()->right()==temp)
                temp->getPadre()->setRight(NULL);
            else
                temp->getPadre()->setLeft(NULL);
        }
        else
        {
            // salvo i dati del nodo da staccare
            binary* pad=temp->getPadre(),
                    *sx=temp->left(),
                    *dx=temp->right();
            // stacco il nodo
            temp->setPadre(NULL);
            temp->setLeft(NULL);
            temp->setRight(NULL);
            // controllo se temp ha figlio destro o meno
            if(!dx)
            {
                // controllo se temp era figlio destro o sinistro
                sx->setPadre(pad);
                // se temp era figlio sinistro aggiorno il figlio sinistro del padre
                if(pad->left()==temp)
                    pad->setLeft(sx);
                else
                    pad->setRight(sx);
            }
            else if(!sx)
            {
                // controllo se temp era figlio destro o sinistro
                dx->setPadre(pad);
                // se temp era figlio sinistro aggiorno il figlio sinistro del padre
                if(pad->left()==temp)
                    pad->setLeft(dx);
                else
                    pad->setRight(dx);
            }
            else
            {
                dx->setPadre(pad);
                // controllo se temp era figlio destro o sinistro del padre
                if(pad->left()==temp)
                    pad->setLeft(dx);
                else
                    pad->setRight(dx);
                // recupero il minimo del figlio destro e setto il suo figlio sinistro col sinistro di temp
                binary* help=minimo(dx);
                help->setLeft(sx);
                help->left()->setPadre(help);
            }
        }
        delete temp;
    }
}
bool BinarySearchTree::search(double i)const
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
BinarySearchTree* BinarySearchTree::copy()
{
    return new BinarySearchTree(getRadice()->copy());
}

void BinarySearchTree::modifica(nodo* n,double info)
{
    cancella(n);
    insert(info);
}
binary* BinarySearchTree::minimo(nodo* n)const
{
    binary* temp=dynamic_cast<binary*>(n);
    while (temp->left())
        temp=temp->left();
    return temp;
}
binary* BinarySearchTree::massimo(nodo* n)const
{
    binary* temp=dynamic_cast<binary*>(n);
    while (temp->right())
        temp=temp->right();
    return temp;
}
double BinarySearchTree::minimo()const
{
    return minimo(getRadice())->getInfo();
}
double BinarySearchTree::massimo()const
{
    return massimo(getRadice())->getInfo();
}

void BinarySearchTree::ordinaHelp(binary* n,QString& q)const
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
QString BinarySearchTree::ordina()const
{
    QString q="[";
    ordinaHelp(getRadice(),q);
    q.remove(q.size()-1,1);
    q+="]";

    return q;
}
binary* BinarySearchTree::operazioneHelp(nodo* n1,nodo* n2,char tipo)const
{
    BinarySearchTree* t=new BinarySearchTree();
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
BinarySearchTree* BinarySearchTree::operazione(Albero* a,char tipo)const
{
    if(!alberiUguali(a))
        throw QString("Alberi di dimensione diversa.Impossibile eseguire l'operazione.");
    BinarySearchTree* temp=new BinarySearchTree();
    temp->setRoot(operazioneHelp(getRadice(),a->getRadice(),tipo));
    return temp;
}
BinarySearchTree* BinarySearchTree::unione(Albero* a)const
{
    vector<double> dati;
    getDati(getRadice(),dati);
    getDati(a->getRadice(),dati);
    BinarySearchTree* ris=new BinarySearchTree();
    for(vector<double>::const_iterator it=dati.begin();it!=dati.end();it++)
        ris->insert(*it);
    return ris;
}
BinarySearchTree* BinarySearchTree::intersezione(Albero* a)const
{
    vector<double> dati1,dati2,dati3;
    getDati(getRadice(),dati1);
    getDati(a->getRadice(),dati2);
    for(vector<double>::iterator it=dati1.begin();it!=dati1.end();it++)
        if(find(dati2.begin(), dati2.end(), *it) != dati2.end())
        {
            vector<double>::iterator it1=dati2.begin();
            while(*it1!=*it)
                it1++;
            dati2.erase(it1);
            dati3.push_back(*it);
        }

    BinarySearchTree* ris=new BinarySearchTree();
    for(vector<double>::const_iterator it=dati3.begin();it!=dati3.end();it++)
        ris->insert(*it);
    return ris;
}
BinarySearchTree* BinarySearchTree::operator+(Albero* a)const
{
    try
    {
        return operazione(a,'+');
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
BinarySearchTree* BinarySearchTree::operator-(Albero* a)const
{
    try
    {
        return operazione(a,'-');
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
BinarySearchTree* BinarySearchTree::operator*(Albero* a)const
{
    try
    {
        return operazione(a,'*');
    }
    catch(QString s)
    {
        throw QString(s);
    };
}
BinarySearchTree* BinarySearchTree::operator/(Albero* a)const
{
    try
    {
        return operazione(a,'/');
    }
    catch(QString s)
    {
        throw QString(s);
    }
}


bool BinarySearchTree::alberiUgualiHelp(nodo* n1,nodo* n2)const
{
    if((n1 && !n2) || (!n1 && n2))
        return false;
    if(!n1 && !n2)
        return true;
    return alberiUgualiHelp(dynamic_cast<binary*>(n1)->left(),dynamic_cast<binary*>(n2)->left()) &&
            alberiUgualiHelp(dynamic_cast<binary*>(n1)->right(),dynamic_cast<binary*>(n2)->right());
}

bool BinarySearchTree::alberiUguali(Albero* a)const
{
    return alberiUgualiHelp(getRadice(),a->getRadice());
}






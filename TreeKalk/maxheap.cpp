
#include "maxheap.h"


maxHeap::maxHeap():heap(){setTipo(QString("maxHeap"));}
maxHeap::maxHeap(const maxHeap& b,QString q):heap(b.getRadice()->copy(),q){setTipo(QString("maxHeap"));}
maxHeap::maxHeap(nodo* n,const QString& q):heap(n,q){setTipo(QString("maxHeap"));}

maxHeap::~maxHeap()
{
    //cout << "~alberobinario()\n";
}

bool maxHeap::operator ==(const maxHeap& b)const
{
    return heap::operator ==(b);
}
bool maxHeap::operator !=(const maxHeap& b)const
{
    return !(operator ==(b));
}
maxHeap& maxHeap::operator =(const maxHeap& b)
{
    if(this!=&b)
    {
        delete getRadice();
        setRoot(b.getRadice()->copy());
    }
    return *this;
}
void maxHeap::heapify(binary* b)
{
    if(b)
    {
        binary* max=b;
        if(b->left() && b->left()->getInfo()>=b->getInfo())
            max=b->left();
        if(b->right() && b->right()->getInfo()>=max->getInfo())
            max=b->right();
        if(max!=b)
        {
            double t=b->getInfo();
            b->setInfo(max->getInfo());
            max->setInfo(t);
            heapify(max);
        }
    }
}
void maxHeap::heapifyUp(binary* b)
{
    if(b && b->getPadre() && b->getInfo()>b->getPadre()->getInfo())
    {
        double t=b->getInfo();
        b->setInfo(b->getPadre()->getInfo());
        b->getPadre()->setInfo(t);
        heapifyUp(b->getPadre());
    }
}

void maxHeap::insert(double i)
{
    if(!getRadice())
        setRoot(new binary(i,NULL,NULL,NULL));
    else
    {
        int dim=dimensione(getRadice());
        QString b=converti(dim+1);
        binary* temp=getRadice();
        int j=1;

        while(j<b.size()-1)
        {
            temp=( b.mid(j,1)=="0" )?temp->left():temp->right();
            j++;
        }
        if(b.mid(b.size()-1,1)=="0")
        {
            temp->setLeft(new binary(i,temp,NULL,NULL));
            heapifyUp(temp->left());
        }
        else if(b.mid(b.size()-1,1)=="1")
        {
            temp->setRight(new binary(i,temp,NULL,NULL));
            heapifyUp(temp->right());
        }
    }

}
void maxHeap::cancella(nodo* n)               // cancella il nodo specifico dall'albero
{
    if(n && !contenuto(n))
        throw std::string("Nodo non contenuto.");
    binary * temp=dynamic_cast<binary*>(ultimo());
    if(temp==getRadice())
    {
        delete getRadice();
        setRoot(NULL);
    }
    else
    {
        if(temp && temp->getPadre())
        {
            if(temp==temp->getPadre()->right())
                temp->getPadre()->setRight(NULL);
            else
                temp->getPadre()->setLeft(NULL);
            temp->setPadre(NULL);
        }
        double i=n->getInfo();
        n->setInfo(temp->getInfo());
        if(n->getInfo()>=i)
            heapifyUp(dynamic_cast<binary*>(n));
        else
            heapify(dynamic_cast<binary*>(n));
        if(temp)
            delete temp;
    }
}
void maxHeap::cancella(double i)              // cancella la prima ricorrenza di i in ordine prefisso
{
    if(!contenuto(i))
        throw std::string("Info non contenuta.");
    cancella(trovaPrimaRicorrenza(i));
}
bool maxHeap::search(double i)const           // ritorna true se trova i nell'albero
{
    return contenuto(i);
}
maxHeap* maxHeap::copy()                       // ritorna una copia dell'albero
{
    return new maxHeap(getRadice()->copy(),getNome());
}
void maxHeap::modifica(nodo* n,double info)   // modifica l'info di un nodo dell'albero
{
    if(info>n->getInfo())
    {
        n->setInfo(info);
        heapifyUp(dynamic_cast<binary*>(n));
    }
    else if(info<n->getInfo())
    {
        n->setInfo(info);
        heapify(dynamic_cast<binary*>(n));
    }
}
void maxHeap::minimoHelp(binary* n,double& min)const                 // ritorna il minimo dell'albero
{

    if(n->getInfo()<min)
        min=n->getInfo();
    if(n->left())
        minimoHelp(n->left(),min);
    if(n->right())
        minimoHelp(n->right(),min);
}
double maxHeap::minimo()const                 // ritorna il minimo dell'albero
{
    if(!getRadice())
        throw std::string("Albero vuoto.");
    double min=getRadice()->getInfo();
    minimoHelp(getRadice(),min);
    return min;
}
double maxHeap::massimo()const
{
    if(!getRadice())
        throw std::string("Albero vuoto.");
    return getRadice()->getInfo();
}
QString maxHeap::ordina()const
{
    binary* temp=getRadice()->copy();
    maxHeap* h=new maxHeap();
    h->setRoot(temp);
    QString q="[";
    while(h->dimensione(h->getRadice())>0)
    {
        q.insert(1, QString::number(h->getRadice()->getInfo()) + ",");
        h->cancella(h->getRadice());
    }
    q.remove(q.size()-1,1);
    q+="]";
    return q;
}

binary* maxHeap::operazioneHelp(nodo* n1,nodo* n2,char tipo)const
{
    maxHeap* t=new maxHeap();
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

maxHeap* maxHeap::operazione(Albero* a,char tipo)const
{
    if(!alberiUguali(a))
        throw QString("Alberi di dimensione diversa.Impossibile eseguire l'operazione.");
    maxHeap* temp=new maxHeap();
    temp->setRoot(operazioneHelp(getRadice(),a->getRadice(),tipo));
    return temp;
}
maxHeap* maxHeap::unione(Albero* a)const
{
    vector<double> dati;
    getDati(getRadice(),dati);
    getDati(a->getRadice(),dati);
    maxHeap* ris=new maxHeap();
    for(vector<double>::const_iterator it=dati.begin();it!=dati.end();it++)
        ris->insert(*it);
    return ris;
}
maxHeap* maxHeap::intersezione(Albero* a)const
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

    maxHeap* ris=new maxHeap();
    for(vector<double>::const_iterator it=dati3.begin();it!=dati3.end();it++)
        ris->insert(*it);
    return ris;
}
maxHeap* maxHeap::operator+(Albero* a)const
{
    return operazione(a,'+');
}
maxHeap* maxHeap::operator-(Albero* a)const
{
    return operazione(a,'-');
}
maxHeap* maxHeap::operator*(Albero* a)const
{
    return operazione(a,'*');
}
maxHeap* maxHeap::operator/(Albero* a)const
{
    return operazione(a,'/');
}











#include "controller.h"


controller::controller(Gview *vis):mod(new model()),v(vis)
{
    connect(this,SIGNAL(risultatoInserimento(QString,QString)),v,SLOT(disp(QString,QString)));
    connect(this,SIGNAL(cancelSignalSottoalbero(QString,QString)),mod,SLOT(cancelSlotSottoalbero(QString,QString)));
    connect(this,SIGNAL(cancelSignalNodo(QString,QString)),mod,SLOT(cancelSlotNodo(QString,QString)));
    connect(this,SIGNAL(modificaNodoSignal(QString,QString,double)),mod,SLOT(modificaNodoSlot(QString,QString,double)));
    connect(this,SIGNAL(cercaSignalRis(QString)),v,SLOT(cercaSlotRis(QString)));
    connect(this,SIGNAL(cancelSignalAlbero(QString)),mod,SLOT(cancelSlotAlbero(QString)));

}

controller::~controller()
{
    delete mod;
    delete v;
}
void controller::inserimentoAlberoSlot(QString albero,QString tipo)
{
    if(albero.contains("#"))
        emit risultatoInserimento("Inserimento fallito",albero);
    else
    {
        bool ris=mod->inserisci(albero,tipo);
        if(ris)
            emit risultatoInserimento("Inserimento riuscito",albero);
        else
            emit risultatoInserimento("Inserimento fallito",albero);
    }
}
void controller::aggiungiNodo(const QString& nome,double info)
{
    mod->inserisciNodoInAlbero(nome,info);
}
Albero* controller::getElemento(const QString& nome)
{
    return (mod->getElemento(nome));
}
void controller::cancelSlotSottoalbero(QString albero, QString nodo)
{
    try
    {
        emit cancelSignalSottoalbero(albero,nodo);
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
void controller::cancelSlotNodo(QString albero, QString nodo)
{
    try
    {
        emit cancelSignalNodo(albero,nodo);
    }
    catch(QString q)
    {
        emit cercaSignalRis(q);
    }
}
void controller::cancelSlotAlbero(QString albero)
{
    emit cancelSignalAlbero(albero);
    throw QString("Cancellazione riuscita.");
}
void controller::modificaNodoSlot(QString albero, QString nodo,double i)
{
    emit modificaNodoSignal(albero,nodo,i);
}
void controller::cercaSlot(QString albero, double i)
{
    if(mod->cerca(albero,i))
        emit cercaSignalRis("Trovato");
    else
        emit cercaSignalRis("Non Trovato");
}
void controller::maxSlot(QString albero)
{
    emit cercaSignalRis(QString::number(mod->massimo(albero)));
}
void controller::minSlot(QString albero)
{
    emit cercaSignalRis(QString::number(mod->minimo(albero)));
}
void controller::orderSlot(QString albero)
{
    try
    {
        emit cercaSignalRis(mod->order(albero));
    }
    catch(std::string s)
    {
        cout << s;
    }
}
void controller::ottieniStampaAlberoSlot(QString albero)
{
    throw QString(stampa(dynamic_cast<binary*>(mod->trovaDaNome(albero)->getRadice())));
}
void controller::operazione(QString a1, QString a2, Albero *a,QString op)
{
    QString nome;
    int i=0;
    while(i<100)
    {
        nome=QString("(") +a1 + op + a2 + QString::number(i)+QString(")");
        if(mod->inserisci(nome,a))
        {
            emit risultatoInserimento("Operazione riuscita.",nome);
            break;
        }
        i++;
    }
}
void controller::piuSlot(QString albero1,QString albero2)
{
    try
    {
        Albero* a1=mod->somma(albero1,albero2);
        operazione(albero1,albero2,a1,QString("+"));
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
void controller::menoSlot(QString albero1,QString albero2)
{
    try
    {
        Albero* a1=mod->sottrai(albero1,albero2);
        operazione(albero1,albero2,a1,QString("-"));
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
void controller::perSlot(QString albero1,QString albero2)
{
    try
    {
        Albero* a1=mod->moltiplica(albero1,albero2);
        operazione(albero1,albero2,a1,QString("*"));
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
void controller::divisoSlot(QString albero1,QString albero2)
{
    try
    {
        Albero* a1=mod->dividi(albero1,albero2);
        operazione(albero1,albero2,a1,QString("/"));
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
void controller::unioneSlot(QString albero1,QString albero2)
{
    try
    {
        Albero* a1=mod->unisci(albero1,albero2);
        operazione(albero1,albero2,a1,QString("U"));
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
void controller::intersezioneSlot(QString albero1,QString albero2)
{
    try
    {
        Albero* a1=mod->interseca(albero1,albero2);
        operazione(albero1,albero2,a1,QString("I"));
    }
    catch(QString s)
    {
        throw QString(s);
    }
}
QString controller::getTipo(QString albero) const
{
    return mod->trovaDaNome(albero)->getTipo();
}

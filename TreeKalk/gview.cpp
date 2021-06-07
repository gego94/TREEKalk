
#include "gview.h"


Gview::Gview(QWidget *parent):QMainWindow(parent)
{
    c=new controller(this),s=new QGraphicsScene(this),v=new QGraphicsView;
    v->setScene(s),resize(this->width()*2,this->height()*2);
    v->centerOn(0,0);

    buttonInserisci = new QPushButton(tr("Inserisci nuovo albero"));
    buttonInserisciNodo = new QPushButton(tr("Aggiungi Nodo"));
    ButtonClose = new QPushButton(tr("Close"));
    zoomin = new QPushButton(tr("Zoom In"));
    zoomout = new QPushButton(tr("Zoom Out"));
    cancellaSottoalbero = new QPushButton(tr("Cancella Sottoalbero"));
    cancellaNodo = new QPushButton(tr("Cancella Nodo"));
    cancellaAlbero = new QPushButton(tr("Cancella Albero"));
    modifica = new QPushButton(tr("Modifica"));
    cerca = new QPushButton(tr("Cerca"));
    piu = new QPushButton(tr("Somma"));meno = new QPushButton(tr("Sottrai"));
    per = new QPushButton(tr("Moltiplica"));diviso = new QPushButton(tr("Dividi"));
    unione = new QPushButton(tr("Unisci"));intersezione = new QPushButton(tr("Interseca"));
    maxButton = new QPushButton(tr("Massimo"));
    minButton = new QPushButton(tr("Minimo"));
    orderButton = new QPushButton(tr("Ordina"));;
    qlInserimentoAlbero=new QLineEdit(),qlInserimentoAlbero->setText("Albero1"),
    qlModifica=new QLineEdit(),qlModifica->setText("0.0"),
    qlCerca=new QLineEdit(),qlCerca->setText("0.0"),
    qlInserimentoNodo=new QLineEdit(),qlInserimentoNodo->setText("0.0");
    qq=new QLineEdit(),qq->setReadOnly(true),qStampaAlbero=new QLineEdit(),qStampaAlbero->setReadOnly(true),
    qAlberoOperazioni=new QLineEdit(),qAlberoOperazioni->setReadOnly(true);
    gridL=new QGridLayout,gridPrincipale=new QGridLayout,gridInserimentoAlbero=new QGridLayout,gridInserimentoNodo=new QGridLayout,
    gridZoom=new QGridLayout,gridDelete=new QGridLayout,gridModifica=new QGridLayout,gridCerca=new QGridLayout;gridOpzioni=new QGridLayout,
    gridOperazioni=new QGridLayout,gridOperazioniEst=new QGridLayout,gridAlbero= new QGridLayout;
    monitor=new QComboBox(),monitorOperazioni=new QComboBox();
    monitorInserimentoAlbero=new QComboBox();aggiungiTipo("BST"),aggiungiTipo("MaxHeap"),aggiungiTipo("MinHeap"),aggiungiTipo("AlberoRB");
    qlTipoAlbero=new QLineEdit();qlTipoOperazione=new QLineEdit();
    this->layout = new QHBoxLayout;

    connect(buttonInserisci, SIGNAL(clicked()),this  , SLOT(aggiungiAlbero()));
    connect(buttonInserisciNodo, SIGNAL(clicked()),this  , SLOT(aggiungiNodo()));
    connect(ButtonClose, SIGNAL(clicked()),this  , SLOT(close()));
    connect(this, SIGNAL(signalInserimento(QString,QString)), c  , SLOT(inserimentoAlberoSlot(QString,QString)));
    connect(this, SIGNAL(aggiungiNodoSignal(QString,double)),c , SLOT(aggiungiNodo(QString,double)));
    connect(zoomin, SIGNAL(clicked()),this  , SLOT(zoomIn()));
    connect(zoomout, SIGNAL(clicked()),this  , SLOT(zoomOut()));
    connect(cancellaSottoalbero, SIGNAL(clicked()),this  , SLOT(cancellaSottoalberoFun()));
    connect(cancellaNodo, SIGNAL(clicked()),this  , SLOT(cancellaNodoFun()));
    connect(cancellaAlbero, SIGNAL(clicked()),this  , SLOT(cancellaAlberoFun()));
    connect(modifica, SIGNAL(clicked()),this  , SLOT(modificaNodoSlot()));
    connect(cerca, SIGNAL(clicked()),this  , SLOT(cercaSlot()));
    connect(maxButton, SIGNAL(clicked()),this  , SLOT(maxSlot()));
    connect(minButton, SIGNAL(clicked()),this  , SLOT(minSlot()));
    connect(orderButton, SIGNAL(clicked()),this  , SLOT(orderSlot()));
    connect(monitor, SIGNAL(currentIndexChanged(int)),this  , SLOT(ridisegna()));
    connect(monitorOperazioni, SIGNAL(currentIndexChanged(int)),this  , SLOT(alberoOperazioni()));
    connect(piu, SIGNAL(clicked()),this  , SLOT(piuSlot()));
    connect(meno, SIGNAL(clicked()),this  , SLOT(menoSlot()));
    connect(per, SIGNAL(clicked()),this  , SLOT(perSlot()));
    connect(diviso, SIGNAL(clicked()),this  , SLOT(divisoSlot()));
    connect(unione, SIGNAL(clicked()),this  , SLOT(unioneSlot()));
    connect(intersezione, SIGNAL(clicked()),this  , SLOT(intersezioneSlot()));
    connect(this, SIGNAL(cancelSignalSottoalbero(QString,QString)),c  , SLOT(cancelSlotSottoalbero(QString,QString)));
    connect(this, SIGNAL(cancelSignalNodo(QString,QString)),c  , SLOT(cancelSlotNodo(QString,QString)));
    connect(this, SIGNAL(cancelSignalAlbero(QString)),c  , SLOT(cancelSlotAlbero(QString)));
    connect(this, SIGNAL(modificaNodoSignal(QString,QString,double)),c  , SLOT(modificaNodoSlot(QString,QString,double)));
    connect(this, SIGNAL(cercaSignal(QString,double)),c  , SLOT(cercaSlot(QString,double)));
    connect(this, SIGNAL(maxSignal(QString)),c  , SLOT(maxSlot(QString)));
    connect(this, SIGNAL(minSignal(QString)),c  , SLOT(minSlot(QString)));
    connect(this, SIGNAL(orderSignal(QString)),c  , SLOT(orderSlot(QString)));
    connect(this, SIGNAL(piuSignal(QString,QString)),c  , SLOT(piuSlot(QString,QString)));
    connect(this, SIGNAL(menoSignal(QString,QString)),c  , SLOT(menoSlot(QString,QString)));
    connect(this, SIGNAL(perSignal(QString,QString)),c  , SLOT(perSlot(QString,QString)));
    connect(this, SIGNAL(divisoSignal(QString,QString)),c  , SLOT(divisoSlot(QString,QString)));
    connect(this, SIGNAL(unioneSignal(QString,QString)),c  , SLOT(unioneSlot(QString,QString)));
    connect(this, SIGNAL(intersezioneSignal(QString,QString)),c  , SLOT(intersezioneSlot(QString,QString)));
    connect(this, SIGNAL(ottieniStampaAlberoSignal(QString)),c  , SLOT(ottieniStampaAlberoSlot(QString)));


    // griglia per lo zoom
    gridZoom->addWidget(zoomin,0,0),gridZoom->addWidget(zoomout,0,1);
    // griglia per inserimento albero
    gridInserimentoAlbero->addWidget(buttonInserisci,0,0),gridInserimentoAlbero->addWidget(qlInserimentoAlbero,0,1),gridInserimentoAlbero->addWidget(monitorInserimentoAlbero,0,2);
    // griglia per inserimento nodo
    gridInserimentoNodo->addWidget(buttonInserisciNodo,0,0),gridInserimentoNodo->addWidget(qlInserimentoNodo,0,1);
    // griglia modifica
    gridModifica->addWidget(modifica,0,0),gridModifica->addWidget(qlModifica,0,1);
    // griglia delete
    gridDelete->addWidget(cancellaSottoalbero,0,0),gridDelete->addWidget(cancellaNodo,0,1),gridDelete->addWidget(cancellaAlbero,1,0),gridDelete->addLayout(gridModifica,1,1);
    // grid cerca
    gridCerca->addWidget(cerca,0,0),gridCerca->addWidget(qlCerca,0,1);
    // grid opzioni
    gridOpzioni->addWidget(maxButton,0,0),gridOpzioni->addWidget(minButton,0,1),gridOpzioni->addWidget(orderButton,0,2);
    // grid operazioni
    gridOperazioni->addWidget(piu,0,0);gridOperazioni->addWidget(meno,0,1);gridOperazioni->addWidget(per,1,0);
    gridOperazioni->addWidget(diviso,1,1);gridOperazioni->addWidget(unione,2,0);gridOperazioni->addWidget(intersezione,2,1),
    gridOperazioniEst->addWidget(monitorOperazioni,1,0);gridOperazioniEst->addLayout(gridOperazioni,0,0);
    gridOperazioniEst->addWidget(qAlberoOperazioni,2,0);gridOperazioniEst->addWidget(qlTipoOperazione,3,0);
    // griglia inserimento alberi
    gridAlbero->addWidget(monitor,0,0),gridAlbero->addWidget(qStampaAlbero,1,0),gridAlbero->addWidget(qlTipoAlbero,2,0);

    gridL->addLayout(gridInserimentoAlbero,0,0),gridL->addLayout(gridInserimentoNodo,1,0),gridL->addLayout(gridZoom,4,0);
    gridL->addLayout(gridAlbero,2,0),gridL->addWidget(ButtonClose,3,0),gridL->addLayout(gridDelete,5,0),
    gridL->addLayout(gridCerca,6,0),gridL->addLayout(gridOpzioni,7,0),gridL->addLayout(gridOperazioniEst,8,0);

    gridPrincipale->addLayout(gridL,0,0),gridPrincipale->addWidget(qq,4,0),gridPrincipale->addWidget(v,0,1);
    // set central widget of the main window
    central_widget = new QWidget;
    central_widget->setLayout(gridPrincipale);
    gridPrincipale->setColumnStretch(1,2);
    this->setCentralWidget(central_widget);
}
Gview::~Gview()
{
    delete layout;
    delete gridL;delete gridPrincipale;delete gridInserimentoAlbero;delete gridInserimentoNodo;delete gridDelete;
    delete gridZoom;delete gridModifica;delete gridCerca;delete gridOpzioni;delete gridOperazioni;
    delete gridOperazioniEst;delete gridAlbero;
    delete s;delete v;
    delete layout;
    delete qlInserimentoAlbero;delete qlInserimentoNodo;delete qlCerca;delete qlModifica;delete qlTipoAlbero;delete qlTipoOperazione;
    delete buttonInserisci;delete buttonInserisciNodo;delete ButtonClose;delete zoomin;delete zoomout;
    delete cancellaSottoalbero;delete cancellaNodo;delete cancellaAlbero;delete modifica;delete cerca;
    delete maxButton;delete minButton;delete orderButton;delete piu;delete meno;delete per;delete diviso;
    delete unione;delete intersezione;
    delete c;
    delete qq;delete qStampaAlbero;delete qAlberoOperazioni;
    delete central_widget;
    delete monitor;delete monitorInserimentoAlbero;delete monitorOperazioni;
    QList<QGraphicsItem*> elementiDaEliminare=v->items();
    for(QList<QGraphicsItem*>::const_iterator it=elementiDaEliminare.begin();it!=elementiDaEliminare.end();it++)
        if(*it)
            delete *it;
}

void Gview::pulisci()
{

    s->clear();
    v->viewport()->update();
}
void Gview::aggiungiAlbero()
{
    emit signalInserimento(qlInserimentoAlbero->text(),monitorInserimentoAlbero->currentText());
}
void Gview::disp(QString q,QString nome)
{
    qq->setText(q);
    if(q=="Inserimento riuscito" || q=="Operazione riuscita.")
    {
        monitor->addItem(nome);
        monitorOperazioni->addItem(nome);
        monitor->setCurrentIndex(monitor->findText(nome));
    }
}
void Gview::aggiungiNodo()
{
    if(monitor->currentText()!="")
    {
        emit aggiungiNodoSignal(monitor->currentText(),qlInserimentoNodo->text().toDouble());
        ridisegna();
        if(monitorOperazioni->currentText()==monitor->currentText())
            alberoOperazioni();
    }
    else
        qq->setText("Nessun albero su cui inserire");
}

void Gview::zoomIn()
{
    v->scale(1.15,1.15);
}
void Gview::zoomOut()
{
    v->scale(1/1.15,1/1.15);
}
void Gview::ridisegna()
{
    pulisci();
    qStampaAlbero->setText(stampabinary(*(dynamic_cast<AlberoBinario*>(c->getElemento(monitor->currentText()))),*s));
    qlTipoAlbero->setText(c->getTipo(monitor->currentText()));
}
void Gview::cancellaSottoalberoFun()
{
    if(monitor->count() && s->selectedItems().size())
    {
        QString n= qgraphicsitem_cast<QGraphicsEllipseItem*>(*(s->selectedItems().begin()))->data(0).toString();
        try
        {
            emit cancelSignalSottoalbero(monitor->currentText(),n);
            if(s->selectedItems().size())
                ridisegna();
        }
        catch(QString s)
        {
            qq->setText(s);
        }
    }
}
void Gview::cancellaNodoFun()
{
    if(monitor->count() && s->selectedItems().size())
    {
        QString n= qgraphicsitem_cast<QGraphicsEllipseItem*>(*(s->selectedItems().begin()))->data(0).toString();
        emit cancelSignalNodo(monitor->currentText(),n);
        if(s->selectedItems().size())
            ridisegna();
    }
}
void Gview::cancellaAlberoFun()
{
    if(monitor->count()==1)
        qq->setText("Cancellazione impossibile.Almeno un albero deve essere sempre presente.");
    else if(monitor->count()>0)
    {
        try
        {
            emit cancelSignalAlbero(monitor->currentText());
        }
        catch(QString s)
        {
            qq->setText(s);
        }
        monitorOperazioni->removeItem(monitor->currentIndex());
        monitor->removeItem(monitor->currentIndex());
    }
}


void Gview::modificaNodoSlot()
{
    if(monitor->count() && s->selectedItems().size())
    {
        QString n= qgraphicsitem_cast<QGraphicsEllipseItem*>(*(s->selectedItems().begin()))->data(0).toString();
        emit modificaNodoSignal(monitor->currentText(),n,qlModifica->text().toDouble());
        if(s->selectedItems().size())
            ridisegna();
    }
}
void Gview::cercaSlot()
{
    if(monitor->count())
        emit cercaSignal(monitor->currentText(),qlCerca->text().toDouble());
}
void Gview::cercaSlotRis(QString ris)
{
    qq->setText(ris);
}
void Gview::aggiungiTipo(QString tipo)
{
    monitorInserimentoAlbero->addItem(tipo);
}
void Gview::maxSlot()
{
    if(monitor->count())
        emit maxSignal(monitor->currentText());
}
void Gview::minSlot()
{
    if(monitor->count())
        emit minSignal(monitor->currentText());
}
void Gview::orderSlot()
{
    if(monitor->count())
        emit orderSignal(monitor->currentText());
}
void Gview::piuSlot()
{
    try
    {
        if(monitor->count())
            emit piuSignal(monitor->currentText(),monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qq->setText(s);
    }
}
void Gview::menoSlot()
{
    try
    {
        if(monitor->count())
            emit menoSignal(monitor->currentText(),monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qq->setText(s);
    }
}
void Gview::perSlot()
{
    try
    {
        if(monitor->count())
            emit perSignal(monitor->currentText(),monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qq->setText(s);
    }
}
void Gview::divisoSlot()
{
    try
    {
        if(monitor->count())
            emit divisoSignal(monitor->currentText(),monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qq->setText(s);
    }
}
void Gview::unioneSlot()
{
    try
    {
        if(monitor->count())
            emit unioneSignal(monitor->currentText(),monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qq->setText(s);
    }
}
void Gview::intersezioneSlot()
{
    try
    {
        if(monitor->count())
            emit intersezioneSignal(monitor->currentText(),monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qq->setText(s);
    }
}
void Gview::alberoOperazioni()
{
    try
    {
        emit ottieniStampaAlberoSignal(monitorOperazioni->currentText());
    }
    catch(QString s)
    {
        qAlberoOperazioni->setText(s);
    }
    qlTipoOperazione->setText(c->getTipo(monitorOperazioni->currentText()));
}

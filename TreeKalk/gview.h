#ifndef GVIEW_H
#define GVIEW_H


#include <QWidget>
#include <QMainWindow>


#include <QString>
#include <QComboBox>
#include <QGridLayout>
#include <QFont>
#include <QScreen>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <math.h>
#include <QDialog>
#include <QLineEdit>
#include <QObject>
#include "controller.h"

class controller;

inline void stampaHelpbinary( binary* n ,QGraphicsScene& s, int xp, int yp,int x,int y,vector<int> nodiL,int liv,int prof)
{

    if(liv)
        s.addLine(xp+20,yp+20,x+20,y+20);
    QGraphicsEllipseItem *i=s.addEllipse(QRectF(x,y,40,40));
    i->setFlag(QGraphicsItem::ItemIsSelectable,true);

    i->setData(0,QString::fromStdString(n->indirizzo()));

    i->setToolTip(QString::number(n->getInfo()));

    // 2^n-1 /2^liv
    //cout << " mi sposto di : " << (((2^(prof))/(2^(liv+1)))) << " 2^prof :" << pow(2,prof) << " 2^liv+1 : " << pow(2,liv+1) <<  endl;
    if(dynamic_cast<rbNodo*>(n))
        if(dynamic_cast<rbNodo*>(n)->getColore()==nero)
            i->setBrush(Qt::black);
        else if(dynamic_cast<rbNodo*>(n)->getColore()==rosso)
            i->setBrush(Qt::red);
        else
            i->setBrush(Qt::green);
    else
        i->setBrush(Qt::blue);
    if(n->left())
        stampaHelpbinary(n->left(),s,x,y,x-(pow(2,prof)/pow(2,liv+1))*50,y+200,nodiL,liv+1,prof);

    if(n->right())
        stampaHelpbinary(n->right(),s,x,y,x+(pow(2,prof)/pow(2,liv+1))*50,y+200,nodiL,liv+1,prof);
}

inline QString stampabinary( AlberoBinario& b ,QGraphicsScene& s)
{
    if(&b && b.getRadice())
    {
        vector<int> nodiL;
        int liv=0;
        while(liv<b.profondita())
        {
            nodiL.push_back(b.nodiLiv(liv));
            liv++;
        }
        stampaHelpbinary(b.getRadice(),s,0,0,0,-800,nodiL,0,b.profondita()-1);
    }
    return stampa(b.getRadice());
}

class Gview : public QMainWindow
{
    Q_OBJECT
private:
    QLayout *layout;
    QGridLayout *gridL,*gridPrincipale,*gridInserimentoAlbero,*gridInserimentoNodo,*gridZoom,*gridDelete,*gridModifica,*gridCerca,
                *gridOpzioni,*gridOperazioni,*gridOperazioniEst,*gridAlbero;
    QLineEdit *qlInserimentoAlbero,*qlInserimentoNodo,*qlModifica,*qlCerca,*qlTipoAlbero,*qlTipoOperazione;
    QPushButton *buttonInserisci,*buttonInserisciNodo,*ButtonClose,*zoomin,*zoomout,
                *cancellaSottoalbero,*cancellaNodo,*cancellaAlbero,*modifica,
                *cerca,*maxButton,*minButton,*orderButton,
                *piu,*meno,*per,*diviso,*unione,*intersezione;

    QGraphicsScene* s;
    QGraphicsView* v;
    controller* c;
    vector<double> a;
    QLineEdit *qq,*qStampaAlbero,*qAlberoOperazioni;
    QWidget * central_widget;
    QComboBox *monitor,*monitorInserimentoAlbero,*monitorOperazioni;

public:
    Gview(QWidget *parent = NULL);
    ~Gview();
    void aggiungiTipo(QString tipo);
signals:
    void signalInserimento(QString albero,QString tipo);
    void aggiungiNodoSignal(const QString q,double info);
    void cancelSignalSottoalbero(QString nome,QString nodo);
    void cancelSignalNodo(QString nome,QString nodo);
    void cancelSignalAlbero(QString nome);
    void modificaNodoSignal(QString nome,QString nodo,double i);
    void cercaSignal(QString nome,double i);
    void maxSignal(QString nome);
    void minSignal(QString nome);
    void orderSignal(QString nome);
    void piuSignal(QString nome1,QString nome2);
    void menoSignal(QString nome1,QString nome2);
    void perSignal(QString nome1,QString nome2);
    void divisoSignal(QString nome1,QString nome2);
    void unioneSignal(QString nome1,QString nome2);
    void intersezioneSignal(QString nome1,QString nome2);
    void ottieniStampaAlberoSignal(QString nome);
public slots:
    void pulisci();
    void aggiungiAlbero();
    void disp(QString q,QString nome);
    void aggiungiNodo();
    void zoomIn();
    void zoomOut();
    void cancellaSottoalberoFun();
    void cancellaNodoFun();
    void cancellaAlberoFun();
    void modificaNodoSlot();
    void ridisegna();
    void cercaSlot();
    void cercaSlotRis(QString ris);
    void maxSlot();
    void minSlot();
    void orderSlot();
    void piuSlot();
    void menoSlot();
    void perSlot();
    void divisoSlot();
    void unioneSlot();
    void intersezioneSlot();
    void alberoOperazioni();
};


#endif // VIEW_H

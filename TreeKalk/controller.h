
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "gview.h"
#include <QObject>

class Gview;
class model;

class controller:public QObject
{
    Q_OBJECT
    model* mod;
    Gview* v;

public:

    controller(Gview *vis=NULL);
    ~controller();
    Albero* getElemento(const QString& nome);
    void operazione(QString a1,QString a2,Albero* a,QString op);
    QString getTipo(QString albero)const;
signals:
    void risultatoInserimento(QString s,QString nome);
    void cancelSignalSottoalbero(QString albero,QString nodo);
    void cancelSignalNodo(QString albero,QString nodo);
    void cancelSignalAlbero(QString albero);
    void modificaNodoSignal(QString albero,QString nodo,double i);
    void cercaSignalRis(QString ris);
    void maxSignal(QString albero);
    void minSignal(QString albero);
    void orderSignal(QString albero);
    void piuSignal(QString albero1,QString albero2);
    void menoSignal(QString albero1,QString albero2);
    void perSignal(QString albero1,QString albero2);
    void divisoSignal(QString albero1,QString albero2);
    void unioneSignal(QString albero1,QString albero2);
    void intersezioneSignal(QString albero1,QString albero2);
public slots:
    void inserimentoAlberoSlot(QString albero,QString tipo);
    void aggiungiNodo(const QString& nome,double info);
    void cancelSlotSottoalbero(QString albero,QString nodo);
    void cancelSlotNodo(QString albero,QString nodo);
    void cancelSlotAlbero(QString albero);
    void modificaNodoSlot(QString albero,QString nodo,double i);
    void cercaSlot(QString albero,double i);
    void maxSlot(QString albero);
    void minSlot(QString albero);
    void orderSlot(QString albero);
    void piuSlot(QString albero1,QString albero2);
    void menoSlot(QString albero1,QString albero2);
    void perSlot(QString albero1,QString albero2);
    void divisoSlot(QString albero1,QString albero2);
    void unioneSlot(QString albero1,QString albero2);
    void intersezioneSlot(QString albero1,QString albero2);
    void ottieniStampaAlberoSlot(QString albero);
};



#endif // CONTROLLER_H

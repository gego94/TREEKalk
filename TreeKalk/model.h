#ifndef MODEL_H
#define MODEL_H

#include "binarysearchtree.h"
#include "maxheap.h"
#include "minheap.h"
#include "rbtree.h"
#include "controller.h"
#include <QObject>

class model:public QObject
{
    Q_OBJECT
    list<Albero*> elementi;
    void rifaiHelp(binary *b,heap* h)const;
public:
    model();
    ~model();
    Albero* trovaDaNome(QString nome)const;
    bool inserisci(QString albero,QString tipo);
    bool inserisci(Albero *a);
    bool inserisci(QString a,Albero* al);
    void inserisciNodoInAlbero(const QString& a,double i);
    void cancella(Albero* a);
    Albero* getElemento(const QString& el);
    bool cerca(QString albero,double i);
    double massimo(QString albero)const;
    double minimo(QString albero)const;
    QString order(QString albero)const;
    Albero* somma(QString albero1,QString albero2)const;
    Albero* sottrai(QString albero1,QString albero2)const;
    Albero* moltiplica(QString albero1,QString albero2)const;
    Albero* dividi(QString albero1,QString albero2)const;
    Albero* unisci(QString albero1,QString albero2)const;
    Albero* interseca(QString albero1,QString albero2)const;
    heap* rifai(heap* h)const;
    bool contiene(QString nome)const;
signals:
    void signalResult(QString r);
public slots:
    void cancelSlotSottoalbero(QString albero,QString nod);
    void cancelSlotNodo(QString albero,QString nod);
    void cancelSlotAlbero(QString albero);
    void modificaNodoSlot(QString albero,QString nodo,double i);
};


#endif // MODEL_H

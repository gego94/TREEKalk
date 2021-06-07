#ifndef ALBEROBINARIO_H
#define ALBEROBINARIO_H

#include "binary.h"
#include "albero.h"

class AlberoBinario;

ostream& operator <<(ostream& o, const AlberoBinario& b);

class AlberoBinario:public Albero
{
    friend ostream& operator <<(ostream& o, const AlberoBinario& b);
    binary* operazioneHelp(binary* n1,binary* n2,char tipo)const;
public:
    AlberoBinario();
    AlberoBinario(const AlberoBinario& b,QString q="");
    AlberoBinario(nodo* n,const QString& q="");
    ~AlberoBinario();
    bool operator ==(const AlberoBinario& b)const;                          // operator == profondo
    bool operator !=(const AlberoBinario& b)const;                          // operator != profondo
    AlberoBinario& operator =(const AlberoBinario& b);                      // operator = profondo
    binary* getRadice()const;

};

inline ostream& operator <<(ostream& o,const AlberoBinario& b)
{
    if(b.getRadice())
        o << *(b.getRadice()) << endl ;
    else
        o << "()";
    return o;
}


#endif // ALBEROBINARIO_H

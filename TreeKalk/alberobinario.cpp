
#include "alberobinario.h"

AlberoBinario::AlberoBinario():Albero(){}
AlberoBinario::AlberoBinario(const AlberoBinario& b,QString q):Albero(b.getRadice()->copy(),q){}
AlberoBinario::AlberoBinario(nodo* n,const QString& q):Albero(n,q){}

AlberoBinario::~AlberoBinario()
{
    //cout << "~alberobinario()\n";
}

bool AlberoBinario::operator ==(const AlberoBinario& b)const
{
    return Albero::operator ==(b);
}
bool AlberoBinario::operator !=(const AlberoBinario& b)const
{
    return !(operator ==(b));
}
AlberoBinario& AlberoBinario::operator =(const AlberoBinario& b)
{
    if(this!=&b)
    {
        delete getRadice();
        setRoot(b.getRadice()->copy());
    }
    return *this;
}

binary* AlberoBinario::getRadice()const
{
    return dynamic_cast<binary*>(Albero::getRadice());
}



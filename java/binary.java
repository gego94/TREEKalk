


public class binary extends nodo
{

    public binary()
    {
        super(2);
    }
    public binary(double i,binary p,binary l,binary r)        // costruttore da parametri
    {
        super(i,p);
        aggiungiNodo(l);
        aggiungiNodo(r);
    }
    public binary(binary b)      // costruttore di copia
    {
        super(b.copy());
    }
    public binary left()         // metodo che ritorna il figlio sinistro del nodo
    {
        return (binary)getNodo(0);
    }
    public binary right()        // metodo che ritorna il figlio destro
    {
        return (binary)getNodo(1);
    }
    public binary getPadre()
    {
        return (binary)super.getPadre();
    }
    public void setLeft(binary n)    // metodo che permette di settare il figlio sinistro
    {
        setFiglio(0,n);
    }
    public void setRight(binary n)   // metodo che permette di settare il figlio destro
    {
        setFiglio(1,n);
    }
    
    public binary copyHelp(binary n, binary p)
    {
        binary temp=new binary(n.getInfo(),p,null,null);
        if(n.left()!=null)
            temp.setLeft(copyHelp(n.left(),temp));
        else
            temp.setLeft(null);
        if(n.right()!=null)
            temp.setRight(copyHelp(n.right(),temp));
        else
            temp.setRight(null);
        
        return temp;
    }
    public binary copy()    // copia il sottoalbero radicato in n
    {
        return copyHelp(this,null);
    }
    public binary successore()
    {
        if(right()==null)
            return this;
        binary temp=right();
        while(temp.left()!=null)
            temp=temp.left();
        return temp;
    }

}

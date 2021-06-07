
public class rbNodo extends binary
{
    private colore col;
    public rbNodo()                                                // costruttore standard
    {
        super();
        col=colore.nero;
    }
    public rbNodo(double i,rbNodo p,rbNodo l,rbNodo r,colore c)       // costruttore da parametri
    {
        super(i,p,l,r);
        col=c;
    }
    public rbNodo( rbNodo b)      // costruttore di copia
    {
        super(b.copy());
        col=b.getColore();
    }
    public rbNodo left()         // metodo che ritorna il figlio sinistro del nodo
    {
        return (rbNodo)super.left();
    }
    public rbNodo right()        // metodo che ritorna il figlio destro
    {
        return (rbNodo)super.right();
    }
    public rbNodo getPadre()
    {
        return (rbNodo)super.getPadre();
    }
    public rbNodo getNonno()
    {
        if(getPadre()==null)
            return null;
        return getPadre().getPadre();
    }
    public rbNodo getZio()
    {
        if(getPadre()==null || getNonno()==null)
            return null;
        if(getNonno().left()!=getPadre())
            return getNonno().right();
        return getNonno().left();
    }
    public rbNodo getFratello()
    {
        if(getPadre()!=null)
            if(getPadre().right()==this)
                return getPadre().left();
            else
                return getPadre().right();
        return null;
    }
    public void setLeft(rbNodo n)    // metodo che permette di settare il figlio sinistro
    {
        super.setLeft(n);
    }
    public void setRight(rbNodo n)   // metodo che permette di settare il figlio destro
    {
        super.setRight(n);
    }
    public void setColore(colore c)
    {
        col=c;
    }
    private rbNodo copyHelp(rbNodo n, rbNodo p)
    {
        rbNodo temp=new rbNodo(n.getInfo(),p,null,null,n.getColore());
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
    public rbNodo copy()    // copia il sottoalbero radicato in n
    {
        return copyHelp(this,null);
    }
    public colore getColore()
    {
        return col;
    }
    
    public static void main(String []args)
    {
    }
}









public abstract class AlberoBinario extends Albero
{


    public AlberoBinario()
    {
        super();
        
    }
    public AlberoBinario( AlberoBinario b)
    {
        super(b.getRadice().copy());
    }
    public AlberoBinario(nodo n)
    {
        super(n);
    }

    public binary getRadice()
    {
        return (binary)(super.getRadice());
    }
     private boolean alberiUgualiHelp(binary n1,binary n2)
    {
        if((n1==null && n2==null) || (n1.numeroFigli()==0 && n2.numeroFigli()==0))
            return true;
        if((n1==null && n2!=null) || ( n1!=null && n2==null ) || ( n1.numeroFigli()!=n2.numeroFigli() ))
            return false;
        boolean ris=true;
        if(n1.left()!=null)
            ris=alberiUgualiHelp(n1.left(),n2.left());
        if(ris && n1.right()!=null)
            ris=alberiUgualiHelp(n1.right(),n2.right());
        return ris;
    }
    public boolean alberiUguali(Albero a) 
    {
        return alberiUgualiHelp((binary)getRadice(),(binary)a.getRadice());
    }
    public static void main(String []args)
    {
    }

}

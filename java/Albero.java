


import java.util.ArrayList;
import java.util.List;


public abstract class Albero
{
    private nodo root=new nodo();
    public Albero()
    {
        root=null;
    }
    public Albero(nodo n)
    {
        root=n.copy();
    }
    public Albero(Albero a)
    {
        root=a.root.copy();
    }
    public int nodiLiv(int l)    // ritorna il numero di nodi a profondità l         
    {
        return root.nodiLiv(l);
    }
    public int profondita()   // ritorna la profondità dell'albero   
    {
        if(root==null)
            return 0;
        return root.profondita();
    }
    public boolean contenuto(nodo n)       // controlla se n è contenuto nell'albero  
    {
        return root.contenuto(n);
    }
    public boolean contenuto(double i)       // controlla se n è contenuto nell'albero  
    {
        return root.contenuto(i);
    }
    public int livelloNodo(nodo n)   // ritorna la profondità del nodo n qualora sia contenuto nell'albero
    {
        if(!contenuto(n))
            return -1;
        int p=0;
        nodo pad=new nodo(n);
        while(pad.getPadre()!=null)
        {
            pad=new nodo(pad.getPadre());
            p++;
        }
        return p;
    }
    public nodo getRadice()
    {
        return root;
    }
    public void setRoot(nodo n)
    {
        root=n;
        n.setPadre(null);
    }

    public int dimensione(nodo n)
    {
        if(n==null)
            return 0;
        if(n.isFoglia()==true)
            return 1;

        int sum=1;
        for(int j=0;j<n.numeroFigli();j++)
            sum+=dimensione(n.getNodo(j));
        return sum;
    }
    private boolean alberiUgualiHelp(nodo n1,nodo n2)
    {
        if((n1==null && n2!=null) || ( n1!=null && n2==null ) || ( n1.numeroFigli()!=n2.numeroFigli() ))
            return false;
        if((n1==null && n2==null) || (n1.numeroFigli()==0 && n2.numeroFigli()==0))
            return true;
        nodo it;
        nodo it1;
        boolean ris=true;
        for(int i=0;(i<n1.numeroFigli() || i<n2.numeroFigli()) && ris==true;i++)
        {
            it=new nodo((binary)n1.getNodo(i).copy());
            it1=new nodo((binary)n2.getNodo(i).copy());
            it.stampa();
            it1.stampa();
            //if(it!=null && it1!=null)
                ris=alberiUgualiHelp(it,it1);
        }
        return ris;
    }
    public boolean alberiUguali(Albero a) 
    {
        return alberiUgualiHelp(root,a.root);
    }
    public void getDati(nodo n, List d)
    {
	if(n!=null)
	{
	    d.add(n.getInfo());
	    for(int i=0;i<n.numeroFigli();i++)
		getDati(n.getNodo(i),d);
	}
    }
    public abstract Albero operazione(Albero a,char tipo)throws exc;
    public abstract Albero unione(Albero a);
    public abstract Albero intersezione(Albero a);
    public abstract Albero operatorpiu(Albero a);
    public abstract Albero operatormeno(Albero a);
    public abstract Albero operatorper(Albero a);
    public abstract Albero operatordiviso(Albero a);
    public abstract void insert(double i);                // inserisce i nell'albero
    public abstract void cancella(nodo n);               // cancella il nodo specifico dall'albero
    public abstract void cancella(double i);              // cancella la prima ricorrenza di i in ordine prefisso
    public abstract boolean search(double i);           // ritorna true se trova i nell'albero
    public abstract Albero copy();                       // ritorna una copia dell'albero
    public abstract void modifica(double i,double info);   // modifica l'info di un nodo dell'albero
    public abstract double minimo();                 // ritorna il minimo dell'albero
    public abstract double massimo();                // ritorna il massimo dell'albero
    
    public static void main(String []args)
    {}
}


import java.util.*;


public class BST extends AlberoBinario
{


    public BST()
    {
        super();
    }
    public BST(BST b)
    {
        super(b.getRadice().copy());
    }
    public BST(binary n)
    {
        super(n);
    }

    public binary operazioneHelp(nodo n1,nodo n2,char tipo)throws exc
    {
	BST t=new BST();
	List dati=new ArrayList();
	List dati1=new ArrayList();
	getDati(n1,dati);
	getDati(n2,dati1);
	if(tipo=='/' && dati1.contains(0))
            throw new exc("Operazione non valida divisione per 0");
	for(int i=0 ; i<dati.size();i++)
	{
            if(tipo=='+')
                t.insert((double)dati.get(i)+(double)dati1.get(i));
            else if(tipo=='-')
                t.insert((double)dati.get(i)-(double)dati1.get(i));
            else if(tipo=='*')
                t.insert((double)dati.get(i)*(double)dati1.get(i));
            else if(tipo=='/')
                t.insert((double)dati.get(i)/(double)dati1.get(i));
            else
                throw new exc("Operazione non valida");
        }
        return t.getRadice();
    }
    public BST intersezione(Albero a)
    {
        List dati1=new ArrayList();
        List dati2=new ArrayList();
        List dati3=new ArrayList();
        getDati(getRadice(),dati1);
        getDati((binary)a.getRadice(),dati2);
        for(int it=0 ;it<dati1.size();it++)
            if(dati2.contains(dati1.get(it)))
            {
                dati3.add(dati1.get(it));
                dati2.remove(dati1.get(it));
            }

        BST ris=new BST();
        for(int it=0 ;it<dati3.size();it++)
            ris.insert((double)dati3.get(it));
        return ris;
    }
    public BST operazione(Albero a,char tipo)throws exc
    {
        if(!alberiUguali(a))
            throw new exc("Alberi di dimensione diversa.Impossibile eseguire l'operazione.");
        BST temp=new BST();
        temp.setRoot(operazioneHelp(getRadice(),a.getRadice(),tipo));
        return temp;
    }
    public BST unione(Albero a)
    {
        List dati=new ArrayList();
        getDati((binary)getRadice(),dati);
        getDati((binary)a.getRadice(),dati);
        BST ris=new BST();
        for(int i=0 ;i<dati.size();i++)
            ris.insert((double)dati.get(i));
        return ris;
    }
    public BST operatorpiu(Albero a)
    {
        return operazione(a,'+');
    }
    public BST operatormeno(Albero a)
    {
        return operazione(a,'-');
    }
    public BST operatorper(Albero a)
    {
        return operazione(a,'*');
    }
    public BST operatordiviso(Albero a)
    {
        return operazione(a,'/');
    }
    private void inserthelp(binary temp,double i)
    {
        if(i>=temp.getInfo())
            if(temp.right()==null)
                temp.setRight(new binary(i,temp,null,null));
            else
                inserthelp(temp.right(),i);
        else
            if(temp.left()==null)
                temp.setLeft(new binary(i,temp,null,null));
            else
                inserthelp(temp.left(),i);
    }
    public void insert(double i)                 // inserisce i nell'albero
    {
        if(getRadice()==null)
            setRoot(new binary(i,null,null,null));
        else
            inserthelp(getRadice(),i);
    }
    public void cancella(nodo n)               // cancella la prima ricorrenza di i in ordine prefisso
    {
    }
    public void cancella(double i)               // cancella la prima ricorrenza di i in ordine prefisso
    {
        binary temp=getRadice();
        if(temp.getInfo()==i)
        {
            if(getRadice().isFoglia()==true)
                setRoot(null);
            else
            {
                if(temp.right()==null)
                    setRoot(getRadice().left());
                else if(temp.left()==null)
                    setRoot(getRadice().right());
                else
                {
                    binary help=minimo(temp.right());
                    setRoot(temp.right());
                    help.setLeft(temp.left());
                }
                getRadice().setPadre(null);
            }
        }
        else
        {
            while(temp.getInfo()!=i)
            {
                if(i>=temp.getInfo())
                    temp=temp.right();
                else
                    temp=temp.left();
            }
            if(temp.isFoglia()==true)
                if(temp.getPadre().right()==temp)
                    temp.getPadre().setRight(null);
                else 
                    temp.getPadre().setLeft(null);
            else
            {
                binary pad=temp.getPadre(),sx=temp.left(),dx=temp.right();
                temp.setLeft(null);
                temp.setRight(null);
                temp.setPadre(null);
                if(dx==null)
                {
                    sx.setPadre(pad);
                    if(pad.left()==temp)
                        pad.setLeft(sx);
                    else
                        pad.setRight(sx);
                }
                else if(sx==null)
                {
                    dx.setPadre(pad);
                    if(pad.left()==temp)
                        pad.setLeft(dx);
                    else
                        pad.setRight(dx);
                }
                else
                {
                    dx.setPadre(pad);
                    if(pad.left()==temp)
                        pad.setLeft(dx);
                    else
                        pad.setRight(dx);
                    binary help=minimo(dx);
                    help.setLeft(sx);
                    help.left().setPadre(help);
                }
            }
        }
        
    
    }
    public boolean search(double i) 
    {
        if(getRadice()==null)
            return false;
        binary temp=getRadice();
        while(temp != null && i!=temp.getInfo())
        {
            if(i>=temp.getInfo())
                temp=temp.right();
            else
                temp=temp.left();
        }
        if(temp==null)
            return false;
        return true;
    }           // ritorna true se trova i nell'albero
    public BST copy() 
    {
        BST b=new BST();
        b.setRoot(getRadice().copy());
        return b;
    }                       // ritorna una copia dell'albero
    public void modifica(double i,double info) 
    {
        if(contenuto(i))
        {
            cancella(i);
            insert(info);
        }
    }   // modifica l'info di un nodo dell'albero
    public double minimo() 
    {
        if(getRadice()==null)
            return 0;
        binary t=getRadice();
        while(t.left()!=null)
            t=t.left();
        return t.getInfo();
    }                 // ritorna il minimo dell'albero
    public double massimo() 
    {
        if(getRadice()==null)
            return 0;
        binary t=getRadice();
        while(t.right()!=null)
            t=t.right();
        return t.getInfo();
    }                // ritorna il massimo dell'albero
    public binary minimo(binary n) 
    {
        if(n.left()==null)
            return n;
        return minimo(n.left());    
    } 
    public String ordinaHelp(binary b)
    {
        String s="";
        if(b.left()!=null)
            s=s+ordinaHelp(b.left());
        s=s+","+Double.toString(b.getInfo());
        if(b.right()!=null)
            s=s+ordinaHelp(b.right());
        return s;
    }
    public String ordina()
    {
        String s="";
        if(getRadice()==null)
            return s;
        s=ordinaHelp(getRadice());
        s=s.substring(1,s.length());
        s="["+s+"]";
        return s;
        
    }
    public static void main(String []args)
    {
        BST a=new BST();
        a.insert(3.0);
        a.insert(5);
        a.insert(1);
        a.insert(5);
        a.insert(8);
        System.out.println("\na :");
        a.getRadice().stampa();
        BST b=new BST();
        b.insert(-12);
        b.insert(1);
        b.insert(-30);
        b.insert(23);
        b.insert(200);
        System.out.println("\nb :");
        b.getRadice().stampa();
        System.out.println("\nmassimo di a :" + a.massimo());
        System.out.println("\nminimo di a :" + a.minimo());
        System.out.println("\na in ordine :" + a.ordina());
        System.out.println("\ncerco 5 in a :" + a.search(5));
        System.out.println("\ncerco 15 in a :" + a.search(15));
        System.out.println("\na+b :");
        a.operatorpiu(b).getRadice().stampa();
        System.out.println("\na-b :");
        a.operatormeno(b).getRadice().stampa();
        System.out.println("\na*b :");
        a.operatorper(b).getRadice().stampa();
        System.out.println("\na/b :");
        a.operatordiviso(b).getRadice().stampa();
        System.out.println("\na unito b :");
        a.unione(b).getRadice().stampa();
        System.out.println("\na intersecato b :");
        a.intersezione(b).getRadice().stampa();
        System.out.println("\ncancello 5 da a: " );
        a.cancella(5);
        a.getRadice().stampa();
    
    }

}

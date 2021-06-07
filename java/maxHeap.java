
import java.util.*;


public class maxHeap extends heap
{

    public maxHeap()
    {
        super();
    }
    public maxHeap(maxHeap m)
    {
        super(m.getRadice().copy());
    }
    public maxHeap(nodo n)
    {
        super(n);
    }
    public void heapify(binary b)
    {
        if(b!=null)
        {
            binary max=b;
            if(b.left()!=null && b.left().getInfo()>b.getInfo())
                max=b.left();
            if(b.right()!=null && b.right().getInfo()>max.getInfo())
                max=b.right();
            if(max!=b)
            {
                double t=b.getInfo();
                b.setInfo(max.getInfo());
                max.setInfo(t);
                heapify(max);
            }
        }
    }
    public void heapifyUp(binary b)
    {
        if(b!=null && b.getPadre()!=null && b.getInfo()>b.getPadre().getInfo())
        {
            double t=b.getInfo();
            b.setInfo(b.getPadre().getInfo());
            b.getPadre().setInfo(t);
            heapifyUp(b.getPadre());
        }
    }
    public void insert(double i)
    {
        if(getRadice()==null)
            setRoot(new binary(i,null,null,null));
        else
        {
            int dim=dimensione(getRadice());
            int j=1;
            String b=converti(dim+1);
            binary temp=getRadice();
            while(j<b.length()-1)
            {
                if(b.charAt(j)=='0')
                    temp=temp.left();
                else if(b.charAt(j)=='1')
                    temp=temp.right();
                j++;
            }
            if(b.charAt(b.length()-1)=='0')
            {
                temp.setLeft(new binary(i,temp,null,null));
                heapifyUp(temp.left());
            }
            else if(b.charAt(b.length()-1)=='1')
            {
                temp.setRight(new binary(i,temp,null,null));
                heapifyUp(temp.right());
            }
        }
    }
    public void cancella(nodo n)
    {
        binary temp=(binary)ultimo();
        if(temp==getRadice())
            setRoot(null);
        else
        {
            if(temp!=null && temp.getPadre()!=null)
            {
                if(temp==temp.getPadre().right())
                    temp.getPadre().setRight(null);
                else
                    temp.getPadre().setLeft(null);
                temp.setPadre(null);
            }
            double i=n.getInfo();
            n.setInfo(temp.getInfo());
            if(n.getInfo()>i)
                heapifyUp((binary)n);
            else
                heapify((binary)n);
        }
    }
    public void cancella(double i)
    {
        cancella(trovaPrimaRicorrenza(i));
    }
    public boolean search(double i)
    {
        return contenuto(i);
    }
    public maxHeap copy()
    {
        maxHeap m=new maxHeap();
        m.setRoot((binary)getRadice().copy());
        return m;
    }
    public void modifica(nodo n,double info)
    {
        n.setInfo(info);
        if(info>n.getInfo())
            heapifyUp((binary)n);
        else if(info<n.getInfo())
            heapify((binary)n);
    }
    public void minimoHelp(binary n,double min)
    {
        if(n.getInfo()<min)
            min=n.getInfo();
        if(n.left()!=null)
            minimoHelp(n.left(),min);
        if(n.right()!=null)
            minimoHelp(n.right(),min);
    }
    public double minimo()
    {
        double min=getRadice().getInfo();
        minimoHelp(getRadice(),min);
        return min;
    }
    public double massimo()
    {
        return getRadice().getInfo();
    }
    public String ordina()
    {
        binary temp=getRadice().copy();
        maxHeap h=new maxHeap();
        h.setRoot(temp);
        String q="";
        String r="";
        while(h.dimensione(h.getRadice())>1)
        {
            q=q+","+temp.getInfo();
            h.cancella(temp.getInfo());
        }
        q=q+","+temp.getInfo();
        q=q.substring(1,q.length());
        q="["+q+"]";
        return q;
    }
    public binary operazioneHelp(nodo n1,nodo n2,char tipo)throws exc
    {
	maxHeap t=new maxHeap();
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
    public maxHeap operazione(Albero a,char tipo)
    {
        maxHeap temp=new maxHeap();
        if(alberiUguali(a)==true)
            temp.setRoot(operazioneHelp(getRadice(),a.getRadice(),tipo));
            
        return temp;
    }
    public maxHeap unione(Albero a)
    {
        List dati=new ArrayList();
        getDati(getRadice(),dati);
        getDati(a.getRadice(),dati);
        maxHeap ris=new maxHeap();
        for(int i=0;i<dati.size();i++)
            ris.insert((double)dati.get(i));
        return ris;
    }
    public maxHeap intersezione(Albero a)
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

        maxHeap ris=new maxHeap();
        for(int it=0 ;it<dati3.size();it++)
            ris.insert((double)dati3.get(it));
        return ris;
    }
    public maxHeap operatorpiu(Albero a)
    {
        return operazione(a,'+');
    }
    public maxHeap operatormeno(Albero a)
    {
        return operazione(a,'-');
    }
    public maxHeap operatorper(Albero a)
    {
        return operazione(a,'*');
    }
    public maxHeap operatordiviso(Albero a)
    {
        return operazione(a,'/');
    }



    public static void main(String []args)
    {
        maxHeap a=new maxHeap();
        a.insert(3.0);
        a.insert(5);
        a.insert(1);
        a.insert(5);
        a.insert(8);
        System.out.println("\na :");
        a.getRadice().stampa();
        maxHeap b=new maxHeap();
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

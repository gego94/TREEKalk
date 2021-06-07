
import java.util.*;


public class minHeap extends heap
{

    public minHeap()
    {
        super();
    }
    public minHeap(minHeap m)
    {
        super(m.getRadice().copy());
    }
    public minHeap(nodo n)
    {
        super(n);
    }
    public void heapify(binary b)
    {
        if(b!=null)
        {
            binary min=b;
            if(b.left()!=null && b.left().getInfo()<b.getInfo())
                min=b.left();
            if(b.right()!=null && b.right().getInfo()<min.getInfo())
                min=b.right();
            if(min!=b)
            {
                double t=b.getInfo();
                b.setInfo(min.getInfo());
                min.setInfo(t);
                heapify(min);
            }
        }
    }
    public void heapifyUp(binary b)
    {
        if(b!=null && b.getPadre()!=null && b.getInfo()<b.getPadre().getInfo())
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
            if(n.getInfo()<i)
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
    public minHeap copy()
    {
        minHeap m=new minHeap();
        m.setRoot((binary)getRadice().copy());
        return m;
    }
    public void modifica(nodo n,double info)
    {
        n.setInfo(info);
        if(info<n.getInfo())
            heapifyUp((binary)n);
        else if(info>n.getInfo())
            heapify((binary)n);
    }
    public double massimoHelp(binary n)
    {
        double max=0;
        if(n.getInfo()>max)
            max=n.getInfo();
        if(n.left()!=null)
            if(massimoHelp(n.left())>max)
                max=massimoHelp(n.left());
        if(n.right()!=null)
            if(massimoHelp(n.right())>max)
                max=massimoHelp(n.right());
        return max;
    }
    public double minimo()
    {
        return getRadice().getInfo();
    }
    public double massimo()
    {
        return massimoHelp(getRadice());
    }
    public String ordina()//////////////////////////////////////////////////
    {
        binary temp=getRadice().copy();
        minHeap h=new minHeap();
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
	minHeap t=new minHeap();
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
    public minHeap operazione(Albero a,char tipo)
    {
        minHeap temp=new minHeap();
        if(alberiUguali(a)==true)
            temp.setRoot(operazioneHelp(getRadice(),a.getRadice(),tipo));
            
        return temp;
    }
    public minHeap unione(Albero a)
    {
        List dati=new ArrayList();
        getDati(getRadice(),dati);
        getDati(a.getRadice(),dati);
        minHeap ris=new minHeap();
        for(int i=0;i<dati.size();i++)
            ris.insert((double)dati.get(i));
        return ris;
    }
    public minHeap intersezione(Albero a)
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

        minHeap ris=new minHeap();
        for(int it=0 ;it<dati3.size();it++)
            ris.insert((double)dati3.get(it));
        return ris;
    }
    public minHeap operatorpiu(Albero a)
    {
        return operazione(a,'+');
    }
    public minHeap operatormeno(Albero a)
    {
        return operazione(a,'-');
    }
    public minHeap operatorper(Albero a)
    {
        return operazione(a,'*');
    }
    public minHeap operatordiviso(Albero a)
    {
        return operazione(a,'/');
    }



    public static void main(String []args)
    {
        minHeap a=new minHeap();
        a.insert(3.0);
        a.insert(5);
        a.insert(1);
        a.insert(5);
        a.insert(8);
        System.out.println("\na :");
        a.getRadice().stampa();
        minHeap b=new minHeap();
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

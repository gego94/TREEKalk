

import java.util.*;
public class rbTree extends BST
{


    public rbTree()
    {
        super();
    }
    public rbTree( rbTree b)
    {
        super(b.getRadice().copy());
    }
    
    public rbTree(nodo n)
    {
        super((binary)n);
    }
    public rbNodo getRadice()
    {
        return (rbNodo)super.getRadice();
    }
    public void insert(rbNodo n)
    {
        rbNodo temp=getRadice();

        if(temp==null)
            setRoot(new rbNodo(n.getInfo(),null,null,null,colore.nero));
        else
            while(true)
                if(n.getInfo()>=temp.getInfo())
                    if(temp.right()==null)
                    {
                        temp.setRight(n);
                        temp.right().setPadre(temp);
                        break;
                    }
                    else
                        temp=temp.right();
                else
                    if(temp.left()==null)
                    {
                        temp.setLeft(n);
                        temp.left().setPadre(temp);
                        break;
                    }
                    else
                        temp=temp.left();
    }

    public void ruotaSx(rbNodo n)
    {
        if(n!=null && n.right()!=null)
        {
            rbNodo beta=n.right().left(),y=n.right();
            if(n==getRadice())
                setRoot(y);

            y.setPadre(n.getPadre());
            if(n.getPadre()!=null && n.getPadre().left()==n)
                n.getPadre().setLeft(y);
            else if(n.getPadre()!=null && n.getPadre().right()==n)
                n.getPadre().setRight(y);

            y.setLeft(n);
            n.setPadre(y);
            n.setRight(beta);
            if(beta!=null)
                beta.setPadre(n);
        }
    }
    public void ruotaDx(rbNodo n)
    {
        if(n!=null && n.left()!=null)
        {
            rbNodo x=n.left(),beta=x.right();
            if(n==getRadice())
                setRoot(x);

            x.setPadre(n.getPadre());

            if(n.getPadre()!=null && n.getPadre().left()==n)
                n.getPadre().setLeft(x);
            else if(n.getPadre()!=null && n.getPadre().right()==n)
                n.getPadre().setRight(x);

            x.setRight(n);
            n.setPadre(x);
            n.setLeft(beta);
            if(beta!=null)
                beta.setPadre(n);
        }
    }
    public void insert5(rbNodo n)
    {
        if(n!=null && n.getPadre()==n.getNonno().left())
        {
            n.getPadre().setColore(colore.nero);
            n.getNonno().setColore(colore.rosso);
            if (n == n.getPadre().left() && n.getPadre() == n.getNonno().left())
                ruotaDx(n.getNonno());
            else
                ruotaSx(n.getNonno());
        }
        else if(n!=null)
        {
            n.getPadre().setColore(colore.nero);
            n.getNonno().setColore(colore.rosso);
            if (n == n.getPadre().right() && n.getPadre() == n.getNonno().right())
                ruotaSx(n.getNonno());
            else
                ruotaDx(n.getNonno());
        }
    }
    public void insert4(rbNodo n)
    {
        if(n!=null && n.getPadre()!=null && n.getPadre()==n.getNonno().left())
        {
            if (n == n.getPadre().right() && n.getPadre()==n.getNonno().left())
            {
                ruotaSx(n.getPadre());
                n = n.left();
            }
            else if (n == n.getPadre().left() && n.getPadre()==n.getNonno().right())
            {
                ruotaDx(n.getPadre());
                n = n.right();
            }
        }
        else if(n!=null)
        {
            if (n == n.getPadre().left() && n.getPadre()==n.getNonno().right())
            {
                ruotaDx(n.getPadre());
                n = n.right();
            }
            else if (n == n.getPadre().right() && n.getPadre()==n.getNonno().left())
            {
                ruotaSx(n.getPadre());
                n = n.left();
            }
        }
        insert5(n);
    }
    public void insert3(rbNodo n)
    {
        if(n.getZio()!=null && n.getZio().getColore()==colore.rosso)
        {
            ((rbNodo)n.getPadre()).setColore(colore.nero);
            ((rbNodo)n.getZio()).setColore(colore.nero);
            ((rbNodo)n.getNonno()).setColore(colore.rosso);
            insert1(n.getNonno());
        }
        else
            insert4(n);
    }
    public void insert2(rbNodo n)
    {
        if(n.getPadre().getColore()==colore.rosso)
            insert3(n);
    }
    public void insert1(rbNodo n)
    {
        if(n.getPadre()==null)
            n.setColore(colore.nero);
        else
            insert2(n);
    }
    public void insert(double i)
    {
        rbNodo n=new rbNodo(i,null,null,null,colore.rosso);
        insert(n);
        insert1(n);
    }

    public void staccaMinimo(rbNodo n)
    {
        rbNodo m=(rbNodo)n.successore();
        //sostituisco l'info
        if(m==null)
            m=n;
        n.setInfo(m.getInfo());
        // controllo se il minimo è una foglia rossa, in tal caso basta cancellarlo
        if(m!=null && m.getColore()==colore.rosso && m.isFoglia()==true)
            m.stacca();// controllo se il minimo ha figlio dx ed è colore.nero
        else if(m!=null && ((m.right()!=null && m.right().getColore()==colore.rosso) ||
                    (m.left()!=null && m.left().getColore()==colore.rosso)) && m.getColore()==colore.nero)
        {
            if(m==m.getPadre().left())
            {
                if(m.left()!=null)
                {
                    m.getPadre().setLeft(m.left());
                    m.left().setPadre(m.getPadre());
                    m.left().setColore(colore.nero);
                }
                else
                {
                    m.getPadre().setLeft(m.right());
                    m.right().setPadre(m.getPadre());
                    m.right().setColore(colore.nero);
                }
            }
            else if(m==m.getPadre().right())
            {
                if(m.left()!=null)
                {
                    m.getPadre().setRight(m.left());
                    m.left().setPadre(m.getPadre());
                    m.left().setColore(colore.nero);
                }
                else
                {
                    m.getPadre().setRight(m.right());
                    m.right().setPadre(m.getPadre());
                    m.right().setColore(colore.nero);
                }
            }
            m.setPadre(null);m.setLeft(null);m.setRight(null);
        }
        else if(m!=null && m.getColore()==colore.nero && m.isFoglia())
        {
            m.setColore(colore.dn);
            delete1(m);
            if(m!=null && m.getColore()==colore.dn)
                m.stacca();
        }
    }
    public void delete6(rbNodo n)
    {
        if(n.getColore()==colore.dn && n.getFratello()!=null && n.getFratello().getColore()==colore.nero)
        {
            if(n.getPadre().left()==n && n.getFratello().right()!=null && n.getFratello().right().getColore()==colore.rosso)
            {
                ruotaSx(n.getPadre());
                n.getNonno().right().setColore(colore.nero);
            }
            else if(n.getPadre().right()==n && n.getFratello().left()!=null && n.getFratello().left().getColore()==colore.rosso)
            {
                ruotaDx(n.getPadre());
                n.getNonno().left().setColore(colore.nero);
            }
            n.getNonno().setColore(n.getPadre().getColore());
            n.getPadre().setColore(colore.nero);
            if(n.isFoglia()==false)
                n.setColore(colore.nero);
        }
    }
    public void delete5(rbNodo n)
    {
        if(n.getColore()==colore.dn && n.getFratello()!=null && n.getFratello().getColore()==colore.nero)
        {
            if(n.getPadre().left()==n &&
                    (n.getFratello().left()!=null && n.getFratello().left().getColore()==colore.rosso) &&
                    ((n.getFratello().right()==null) || n.getFratello().right().getColore()==colore.nero))
            {
                ruotaDx(n.getFratello());
                colore c=n.getFratello().getColore();
                n.getFratello().setColore(n.getFratello().right().getColore());
                n.getFratello().right().setColore(c);
            }
            else if(n.getPadre().right()==n &&
                    (n.getFratello().right()!=null && n.getFratello().right().getColore()==colore.rosso) &&
                    ((n.getFratello().left()==null) || n.getFratello().left().getColore()==colore.nero))
            {
                ruotaSx(n.getFratello());
                colore c=n.getFratello().getColore();
                n.getFratello().setColore(n.getFratello().left().getColore());
                n.getFratello().left().setColore(c);
            }
        }
        delete6(n);
    }
    public void delete4(rbNodo n)
    {
        if(n.getColore()==colore.dn && n.getPadre().getColore()==colore.rosso && n.getFratello()!=null &&
                n.getFratello().getColore()==colore.nero &&
                    ((n.getFratello().left()==null) || n.getFratello().left().getColore()==colore.nero) &&
                    ((n.getFratello().right()==null) || n.getFratello().right().getColore()==colore.nero))
        {
            n.getPadre().setColore(colore.nero);
            n.getFratello().setColore(colore.rosso);
            if(n.isFoglia()==false)
                n.setColore(colore.nero);
        }
        else
            delete5(n);
    }
    public void delete3(rbNodo n)
    {
        if(n.getColore()==colore.dn && n.getPadre().getColore()==colore.nero &&
            n.getFratello()!=null && n.getFratello().getColore()==colore.nero &&
                ((n.getFratello().left()==null) || n.getFratello().left().getColore()==colore.nero) &&
                ((n.getFratello().right()==null) || n.getFratello().right().getColore()==colore.nero))
        {
            n.getFratello().setColore(colore.rosso);
            n.getPadre().setColore(colore.dn);
            if(n.isFoglia()==false)
                n.setColore(colore.nero);
            delete1(n.getPadre());
        }
        delete4(n);
    }
    public void delete2(rbNodo n)
    {
        if(n.getPadre().getColore()==colore.nero && n.getFratello()!=null &&  n.getFratello().getColore()==colore.rosso &&
                ((n.getFratello().left()==null) || n.getFratello().left().getColore()==colore.nero) &&
                ((n.getFratello().right()==null) || n.getFratello().right().getColore()==colore.nero))
        {
            if(n.getPadre().left()==n)
                ruotaSx(n.getPadre());
            else if(n.getPadre().right()==n)
                ruotaDx(n.getPadre());
            colore c=n.getPadre().getColore();
            n.getPadre().setColore(n.getNonno().getColore());
            n.getNonno().setColore(c);
        }
        delete3(n);
    }
    public void delete1(rbNodo n)
    {
        if(getRadice()==n && n.getColore()==colore.dn)
            n.setColore(colore.nero);
        else if(n!=null && n.getPadre()!=null)
            delete2(n);
    }
    public void cancella(nodo n)
    {
        if(n!=null && n==getRadice() && n.isFoglia()==true)
            setRoot(null);
        else
            staccaMinimo((rbNodo)n);
    }
    public void cancella(double i)
    {
        rbNodo n=getRadice();
        while (n!=null && n.getInfo()!=i)
        {
            if(i<n.getInfo())
                n=n.left();
            else
                n=n.right();
        }
        if(n!= null && n.getInfo()==i)
            cancella(n);
    }

    public boolean search(double i)
    {
        binary temp=getRadice();
        if(temp==null)
            return false;
        while(temp!=null)
        {
            if(temp.getInfo()==i)
                return true;
            if(i>=temp.getInfo())
                temp=temp.right();
            else
                temp=temp.left();
        }
        return false;
    }
    public rbTree copy()
    {
        rbTree r=new rbTree();
        r.setRoot(getRadice().copy());
        return r;
    }
    public void modifica(nodo n,double info)
    {
        cancella(n);
        insert(info);
    }
    rbNodo minimo(nodo n)
    {
        rbNodo temp=(rbNodo)n;
        while (temp.left()!=null)
            temp=temp.left();
        return temp;
    }
    public rbNodo massimo(nodo n)
    {
        rbNodo temp=(rbNodo)n;
        while (temp.right()!=null)
            temp=temp.right();
        return temp;
    }
    public double minimo()
    {
        return minimo(getRadice()).getInfo();
    }
    public double massimo()
    {
        return massimo(getRadice()).getInfo();
    }
    public rbNodo operazioneHelp(nodo n1,nodo n2,char tipo)throws exc
    {
	rbTree t=new rbTree();
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
    public rbTree operazione(Albero a,char tipo)
    {
        rbTree temp=new rbTree();
        if(alberiUguali(a)==true)
            temp.setRoot(operazioneHelp(getRadice(),a.getRadice(),tipo));
            
        return temp;
    }
    public rbTree unione(Albero a)
    {
        List dati=new ArrayList();
        getDati(getRadice(),dati);
        getDati(a.getRadice(),dati);
        rbTree ris=new rbTree();
        for(int i=0;i<dati.size();i++)
            ris.insert((double)dati.get(i));
        return ris;
    }
    public rbTree intersezione(Albero a)
    {
        List dati1=new ArrayList();
        List dati2=new ArrayList();
        List dati3=new ArrayList();
        getDati(getRadice(),dati1);
        getDati(a.getRadice(),dati2);
        for(int it=0 ;it<dati1.size();it++)
            if(dati2.contains(dati1.get(it)))
            {
                dati3.add(dati1.get(it));
                dati2.remove(dati1.get(it));
            }

        rbTree ris=new rbTree();
        for(int it=0 ;it<dati3.size();it++)
            ris.insert((double)dati3.get(it));
        return ris;
    }
    public rbTree operatorpiu(Albero a)
    {
        return operazione(a,'+');
    }
    public rbTree operatormeno(Albero a)
    {
        return operazione(a,'-');
    }
    public rbTree operatorper(Albero a)
    {
        return operazione(a,'*');
    }
    public rbTree operatordiviso(Albero a)
    {
        return operazione(a,'/');
    }

    public static void main(String []args)
    {
        rbTree a=new rbTree();
        a.insert(3.0);
        a.insert(5);
        a.insert(1);
        a.insert(5);
        a.insert(8);
        System.out.println("\na :");
        a.getRadice().stampa();
        rbTree b=new rbTree();
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

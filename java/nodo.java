
import java.util.ArrayList;
import java.util.List;

public class nodo
{
    private double info;
    private nodo padre;
    private List<nodo> nodi=new ArrayList<nodo>();;
    
    public nodo()
    {
        padre=null;
        info=0;
    }
    public nodo(nodo n)
    {
        info=n.info;
        padre=n.padre;
        /*for(int i=0;i<nodi.size();i++)
        {
            nodi.add(n.nodi.get(i).copy());
            nodi.get(i).setPadre(this);
        }*/
    }
    public nodo(int num)
    {
        padre=null;
        info=0;
        for(int i=0;i<num;i++)
        {
            nodi.add(new nodo());
            nodi.get(i).setPadre(this);
        }
    }
    private nodo copyHelp(nodo n,nodo p)
    {
        nodo temp=new nodo();
        temp.info=n.info;
        temp.padre=p;
        
        for(int i=0;i<n.nodi.size();i++)
        {
            if(n.nodi.get(i)!=null)
            {
                nodi.add(copyHelp(n.nodi.get(i),temp));
                nodi.get(i).setPadre(this);
            }
            else
                nodi.add(null);
        }
        return temp;
    }
    public nodo copy()
    {
        return copyHelp(this,null);
    }
    public nodo(double i,nodo p,List<nodo> n)
    {
        info=i;
        padre=p;
        nodi=n;
    }
    public nodo(double i,nodo p)
    {
        info=i;
        padre=p;
    }
    public int numeroFigli()
    {
        return nodi.size();
    }
    public nodo getNodo(int i) throws exc
    {
        if(i>nodi.size())
            throw new exc("Nodo non esistente.");
        return nodi.get(i);
    }
    public nodo getPadre()
    {
        return padre;
    }
    public double getInfo()
    {
        return info;
    }
    public void setInfo(double i)
    {
        info=i;
    }
    public void setPadre(nodo p)
    {
        padre=p;
    }
    public void setFiglio(int i,nodo n)
    {
        if(i>nodi.size())
            throw new exc("Nodo non esistente.");
        nodi.set(i,n);
    }
    public boolean equals(nodo n)
    {
        if(info!=n.info || nodi.size()!=n.nodi.size())
            return false;
        boolean ris=true;
        for(int i=0;i<nodi.size() && ris;i++)
            if((nodi.get(i)== null && n.nodi.get(i)!=null) || (nodi.get(i)!= null && n.nodi.get(i)==null))
                return false;
            else if(nodi.get(i)!= null && n.nodi.get(i)!=null)
                ris=nodi.get(i).equals(n.nodi.get(i));
        return ris;
    }
    public boolean contenuto(double i)
    {
        if(i==info)
            return true;
        boolean ris=false;
        for(int it=0;it<nodi.size() && !ris;it++)
            if(nodi.get(it)!=null)
                ris=nodi.get(it).contenuto(i);
        return ris;
    }
    public boolean contenuto(nodo n)
    {
        if(this==n)
            return true;
        boolean ris=false;
        for(int it=0;it<nodi.size() && !ris;it++)
            if(nodi.get(it)!=null)
                ris=nodi.get(it).contenuto(n);
        return ris;
    }
    public int profondita()
    {
        int t1=0,t2=0;
        for(int i=0;i<nodi.size();i++)
        {
            if(nodi.get(i)!=null)
                t1=nodi.get(i).profondita();
            if(t1>t2)
                t2=t1;
        }
        return t2+1;
    }
    public void aggiungiNodo(nodo n)
    {
        nodi.add(n);
        //n.padre=this;
    }
    public boolean isFoglia()
    {
        if(nodi.size()==0)
            return true;
        for(int i=0;i<nodi.size();i++)
            if(nodi.get(i)!=null)
                return false;
        return true;
    }
    public int nodiLiv(int liv)
    {
        if(liv==0)
            return 1;
        if(liv>profondita() || nodi.size()==0)
            return 0 ;
        int sum=0;
        for(int i=0;i<nodi.size();i++)
            if(nodi.get(i)!=null)
                sum+=nodi.get(i).nodiLiv(liv-1);
        return sum;
    }
    public void distruggi()
    {
        for(int i=0;i<nodi.size();i++)
            if(nodi.get(i)!=null)
                nodi.get(i).distruggi();
        int it=0;
        if(padre!=null)
        {
            while (padre.nodi.get(it)!=this)
                it++;
            padre.nodi.set(it,null);
            padre=null;
        }
    }
    public void stacca()
    {
        int i=0;
        for(;i<padre.nodi.size();i++)
            if(this==padre.nodi.get(i))
            {
                padre.nodi.set(i,null);
                break;
            }
        padre = null;
        i=0;
        for(;i<nodi.size();i++)
        {
            if(nodi.get(i)!=null)
            {
                nodi.get(i).setPadre(null);
                nodi.set(i,null);
            }
        }
    }
    private void stampa1()
    {
        if(padre!=null && padre.nodi.get(padre.nodi.size()-1)==this)
            System.out.print("(" + info );
        else
            System.out.print("(" + info );
        int i=0;
        for(;i<nodi.size();i++)
        {
            if(nodi.get(i)!=null)
                nodi.get(i).stampa1();
            else
                if(i==nodi.size()-1)
                    System.out.print("()");
                else
                    System.out.print("(),");
        }
        System.out.print(")");
    }
    public void stampa()
    {
        System.out.println();
        stampa1();
        
    }
}

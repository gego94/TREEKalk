


public abstract class heap extends BST
{
    public heap()
    {
        super();
    }
    public heap(heap h)
    {
        super(h.getRadice().copy());
    }
    public heap(nodo n)
    {
        super((binary)n);
    }
    public String converti(int i)
    {
        int a;
        String x="";
        while(i > 0)
        {
            a = i % 2;
            x = a+x;
            i = i / 2;
        }
        return x;
    }
    public binary ultimo()
    {
        String b=converti(dimensione(getRadice()));
        binary temp=getRadice();
        int j=1;
        while(j<b.length())
        {
            if( b.charAt(j)=='0')
                temp=temp.left();
            else if(b.charAt(j)=='1')
                temp=temp.right();
            j++;
        }
        return temp;
    }

    public binary trovaPrimaRicorrenza(double i)
    {
        return trovaPrimaRicorrenzaHelp(i,getRadice());
    }
    public binary trovaPrimaRicorrenzaHelp(double i,binary n)
    {
        if(n==null)
            return null;
        binary temp=null;
        if(i==n.getInfo())
            return n;
        if(temp==null && n.left()!=null)
            temp=trovaPrimaRicorrenzaHelp(i,n.left());
        if(temp!=null && n.right()==null)
            temp=trovaPrimaRicorrenzaHelp(i,n.right());
        return temp;
    }
    public abstract void heapify(binary b);
    public abstract void heapifyUp(binary b);


    public static void main(String []args)
    {
    }

}

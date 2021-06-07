

public class Use
{

    public static void main(String []args)
    {
        BST a=new BST();
        a.insert(20);
        a.insert(5);
        a.insert(1);
        a.insert(6);
        a.insert(30);
        System.out.println("\na :");
        a.getRadice().stampa();
        minHeap b=new minHeap();
        b.insert(-12);
        b.insert(1);
        b.insert(-30);
        b.insert(23);
        b.insert(100);
        System.out.println("\nb :");
        b.getRadice().stampa();
        maxHeap c=new maxHeap();
        c.insert(75);
        c.insert(-4);
        c.insert(63);
        c.insert(-758);
        c.insert(-99);
        System.out.println("\nc :");
        c.getRadice().stampa();
        rbTree d=new rbTree();
        d.insert(46);
        d.insert(100);
        d.insert(-45);
        d.insert(-70);
        d.insert(20);
        System.out.println("\nd :");
        d.getRadice().stampa();
        System.out.println("\nmassimo di a :" + a.massimo());
        System.out.println("\nminimo di a :" + a.minimo());
        System.out.println("\na in ordine :" + a.ordina());
        System.out.println("\ncerco 5 in a :" + a.search(5));
        System.out.println("\ncerco 15 in a :" + a.search(15));
        System.out.println("\na+b :");
        a.operatorpiu(b).getRadice().stampa();
        System.out.println("\nb-c :");
        b.operatormeno(c).getRadice().stampa();
        System.out.println("\nc*d :");
        c.operatorper(d).getRadice().stampa();
        System.out.println("\nd/a :");
        d.operatordiviso(a).getRadice().stampa();
        System.out.println("\na unito c :");
        a.unione(c).getRadice().stampa();
        System.out.println("\nb intersecato d :");
        b.intersezione(d).getRadice().stampa();
        System.out.println("\ncancello 5 da a: " );
        a.cancella(5);
        a.getRadice().stampa();
        System.out.println("\nmodifico 6 in 65 da a: " );
        a.modifica(6,65);
        a.getRadice().stampa();
    
    }


}

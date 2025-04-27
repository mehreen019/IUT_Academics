public class App {
    public static void main(String[] args) throws Exception {
        /*Cube c1 = new Cube(4);
        c1.calculateVolume();*/

        //base s1 = new base();
        /*App o = new App();
        Object s1 = o;
        System.out.println(s1 instanceof base);*/


        int i=-10;
        System.out.println(--i);
        System.out.println(i++);
        /*List<base> ll = new ArrayList<base>;
        ll.add("c");
        System.out.println("ok");
        ll.remove("c++");*/
        //System.out.println(s1.m());
        /*s1.calculateSurfaceArea();

        EnigmaMachine em = new EnigmaMachine();
        //em.encode("test.txt", 7);
        em.decode("test.txt", 7);*/

        
    }
}

class base{
    int x=2;
    int m(){
        return x;
    }
}

class t extends base{
    int x=3;
    int m(){
        return x;
    }
}

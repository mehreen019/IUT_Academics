import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        //System.out.println("Hello, World!");

        Coffee darkCoffee = new Coffee("Dark", 78.4f, "Hot");
        Juice OJ = new Juice("Orange juice", 12.5f, "Orange");

        Cup cup1 = new Cup("Red", darkCoffee);
        Cup cup2 = new Cup("Green", OJ);
        System.out.println(cup1.color);
        System.out.println(cup2.color);
        
        cup1.drink();
        cup2.drink();

        System.out.println("Total cups are: "+ Cup.cupCount);

        /*Scanner scan = new Scanner(System.in);
        String o = scan.nextLine();
        System.out.println(o);*/

    }
}

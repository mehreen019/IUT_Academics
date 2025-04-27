public class MobileHome implements Home, Vehicle{
    String name = "MobileHome";

    void getName(){
        System.out.println(name);
    }

    public void go(){
        System.out.println("The mobile home is moving!");
    }

    public void cookFood(){
        System.out.println("Food is being cooked!");
    }
}
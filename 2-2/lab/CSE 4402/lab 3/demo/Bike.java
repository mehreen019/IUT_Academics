/*public class Bike extends Vehicle{
    @Override
    void go(){
        System.out.println("The bike is moving!");
    }
}*/

public class Bike implements Vehicle{
    String name = "Bike";

    void getName(){
        System.out.println(name);
    }

    public void go(){
        System.out.println("The bike is moving!");
    }
}

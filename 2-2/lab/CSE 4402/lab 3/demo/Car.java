/*public class Car extends Vehicle{
    @Override
    void go(){
        System.out.println("The car is moving!");
    }
}*/

public class Car implements Vehicle{
    String name = "Car";

    void getName(){
        System.out.println(name);
    }

    public void go(){
        System.out.println("The car is moving!");
    }
}

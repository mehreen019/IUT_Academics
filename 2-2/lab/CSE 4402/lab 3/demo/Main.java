public class Main{
    public static void main(String[] args){
       // Vehicle v1 = new Vehicle(); //can't be instantiated
        Car c1 = new Car();
        Bike b1 = new Bike();

        c1.go();
        b1.go();

        MobileHome mh1 = new MobileHome();
        mh1.go();
        mh1.cookFood();
    }
}


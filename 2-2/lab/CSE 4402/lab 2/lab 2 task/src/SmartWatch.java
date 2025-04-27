public class SmartWatch extends Device{

    SmartWatch(String name, int price){
        super(name, price);
    }

    void checkingVitals(){
        System.out.println("checking vitals right now!");
    }

    void powerOn(){
        System.out.println("Smartwatch turning on");
    }
    void powerOff(){
        System.out.println("Smartwatch turning off");
    }
}
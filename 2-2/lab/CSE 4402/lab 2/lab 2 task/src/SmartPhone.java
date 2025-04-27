public class SmartPhone extends Device{
    String phoneNum;

    SmartPhone(String name, int price, String num){
        super(name, price);
        this.phoneNum = num;
    }

    void call(String nextNum){
        System.out.println("calling " + nextNum + " from " + phoneNum);
    }

    void powerOn(){
        System.out.println("Smartphone turning on");
    }
    void powerOff(){
        System.out.println("Smartphone turning off");
    }
}
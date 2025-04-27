public class SmartDevice extends Device{
    String[] listOfDevices;

    SmartDevice(String name, int price, String[] arr){
        super(name, price);
        this.listOfDevices = arr;
    }

    void listDevices(){
        System.out.println("Connected devices are: ");
        for(int i=0; i<listOfDevices.length ; i++){
            System.out.println(listOfDevices[i]);
        }
    }

    void powerOn(){
        System.out.println("Smartdevice turning on");
    }
    void powerOff(){
        System.out.println("Smartdevice turning off");
    }
}
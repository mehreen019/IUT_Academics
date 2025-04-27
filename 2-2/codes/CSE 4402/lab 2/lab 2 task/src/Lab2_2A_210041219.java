public class Lab2_2A_210041219 {
    public static void main(String[] args) throws Exception {
        //System.out.println("Hello, World!");
        String[] arr = new String[]{"clock", "fridge", "stove", "curtains"};
        SmartDevice sd = new SmartDevice("very smart device", 505, arr);
        sd.powerOn();
        System.out.println("device name is: "+ sd.name);
        sd.listDevices();
        sd.powerOff();

        SmartPhone sp = new SmartPhone("very smart phone", 1007, "0123456789");
        sp.powerOn();
        System.out.println("device name is: "+ sp.name);
        sp.call("0987654321");
        sp.powerOff();

        SmartWatch sw = new SmartWatch("very smart watch", 766);
        sw.powerOn();
        System.out.println("device name is: "+ sw.name);
        sw.checkingVitals();
        sw.powerOff();
    }
}

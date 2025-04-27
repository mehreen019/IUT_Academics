public class Device{
        String name;
        static int serialNumber = 0;
        int price;

        Device(String Name, int price){
            serialNumber++;
            this.name = Name + " - " + Integer.toString(serialNumber);
            this.price = price;
        }

        void powerOn(){
            System.out.println("device turning on");
        }
        void powerOff(){
            System.out.println("device turning off");
        }
}
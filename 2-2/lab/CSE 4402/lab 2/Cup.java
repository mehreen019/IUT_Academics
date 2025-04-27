public class Cup{
    String color;
    Boolean isFull = true;

    public void drink(){
        if(isFull){
            System.out.println("Taking a drink");
            isFull=false;
        }
        else{
            System.out.println("Can't drink cause the cup is empty :(");
        }
    }
}
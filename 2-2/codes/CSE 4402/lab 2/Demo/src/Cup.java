public class Cup{
    String color = "blue";
    Boolean isFull = true;
    Beverage beverage;
    static int cupCount = 0;

    public Cup(String color, Beverage bvg){
        this.color = color;
        this.isFull = true;
        this.beverage = bvg;
        cupCount++;
    }

    public void drink(){
        if(isFull){
            System.out.println(beverage.drinkName());
            isFull=false;
        }
        else{
            System.out.println("Can't drink cause the cup is empty :(");
        }
    }
}
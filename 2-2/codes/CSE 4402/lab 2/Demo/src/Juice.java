public class Juice extends Beverage{
    String type;
    public Juice(String name, float temp, String type){
        super(name, temp);
        this.type = type;
    }
    String drinkName(){
        return "I'm drinking juice";
    }
}
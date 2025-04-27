public class Coffee extends Beverage{
    String type;
    public Coffee(String name, float temp, String type){
        super(name, temp);
        this.type = type;
    }

    String drinkName(){
        return "I'm drinking coffee";
    }
}
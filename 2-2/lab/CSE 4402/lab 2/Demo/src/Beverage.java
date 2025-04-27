public class Beverage{
    String name;
    float temperature;

    public Beverage(String name, float temp){
        this.name = name;
        this.temperature = temp;
    }

    String drinkName(){
        return "I'm drinking a drink";
    }
}
import java.lang.Math;

public class Cube extends Shape3D{

    double length;
    double volume;
    double surfaceArea;

    Cube(double len){
        this.length=len;
    }

    @Override
    void calculateSurfaceArea(){
        this.volume= Math.pow(length, 3);
        System.out.println("Cube's surface area is: "+ volume);
    }

    @Override
    void calculateVolume(){
        this.surfaceArea = Math.pow(length, 2);
        System.out.println("Cube's volume is: "+ surfaceArea);
    }
}
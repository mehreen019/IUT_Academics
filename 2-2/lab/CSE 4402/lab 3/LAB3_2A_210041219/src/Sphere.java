import java.lang.Math;

public class Sphere extends Shape3D{

    double radius;
    double volume;
    double surfaceArea;

    Sphere(double rad){
        this.radius=rad;
    }

    @Override
    void calculateSurfaceArea(){
        this.surfaceArea = 2*3.1416* Math.pow(radius, 2);
        System.out.println("Sphere's surface area is: "+ surfaceArea);
    }

    @Override
    void calculateVolume(){
        this.volume= (4/3)*3.4146*Math.pow(radius , 3);
        System.out.println("Sphere's volume is: "+ volume);
    }
}
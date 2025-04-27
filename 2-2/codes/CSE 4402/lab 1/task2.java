import java.lang.Math;
import java.util.Random;
import java.util.Scanner;

public class task2{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("The number to compute factorial: ");
        int fact = scan.nextInt();
        int ans=1;
        for(int i=1; i<=fact ; i++){
            ans*=i;
        }
        System.out.println("Factorial is: " + ans);
    }
}
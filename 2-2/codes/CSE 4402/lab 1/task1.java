import java.lang.Math;
import java.util.Random;
import java.util.Scanner;

public class task1{
    public static void main(String[] args){
        Random r = new Random();
        Scanner scan = new Scanner(System.in);
        int low = 0;
        int high = 6;
        int num = r.nextInt(high-low);
        System.out.println("I have rolled a dice.");
        System.out.println("Your guess: ");
        int guess = scan.nextInt();
        if(guess == num){
            System.out.println("Correct!");
        }
        else{
            System.out.println("Wrong! Correct answer is "+num);
        }
    }
}
import java.io.FileWriter; 
import java.io.IOException;
import java.io.FileNotFoundException; 
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;

public class EnigmaMachine implements Encoder, Decoder{
    String temp = "", rd="";
    BufferedReader fr = null;

    public void encode(String fileName, int key){
        try
        {
            fr = new BufferedReader(new FileReader(fileName));
            while ((rd=fr.readLine()) != null){
                temp = temp + rd;
            }
        } 
        catch (FileNotFoundException fe) 
        { 
            System.out.println("File not found"); 
        } 
        catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(temp);

        StringBuffer result= new StringBuffer();
 
        for (int i=0; i<temp.length(); i++)
        {
            if(temp.charAt(i)!=' '){
                if (Character.isUpperCase(temp.charAt(i)))
                {
                    char ch = (char)(((int)temp.charAt(i) + key - 65) % 26 + 65);
                    result.append(ch);
                }
                else
                {
                    char ch = (char)(((int)temp.charAt(i) + key - 97) % 26 + 97);
                    result.append(ch);
                }
            }
            else result.append(' ');      
        }
        
        //temp=result;
        System.out.println(result);
        File file = new File(fileName);

        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file))) {
            for(int i=0;i<result.length();i++){
                bw.write(result.charAt(i));
            }
            bw.newLine();
            //bw.write("This is another line.");
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void decode(String fileName, int key){
        try
        {
            fr = new BufferedReader(new FileReader(fileName));
            while ((rd=fr.readLine()) != null){
                temp = temp + rd;
            }
        } 
        catch (FileNotFoundException fe) 
        { 
            System.out.println("File not found"); 
        } 
        catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(temp);

        StringBuffer result= new StringBuffer();
 
        for (int i=0; i<temp.length(); i++)
        {
            if(temp.charAt(i)!=' '){
                if (Character.isUpperCase(temp.charAt(i)))
                {
                    int k= ((int)temp.charAt(i) - key - 65);
                    if(k<0) k= 26+k;
                    char ch = (char)(k + 65);
                    result.append(ch);
                }
                else
                {
                    int k= ((int)temp.charAt(i) - key - 97);
                    if(k<0) k= 26+k;
                    char ch = (char)(k + 97);
                    result.append(ch);
                }
            }
            else result.append(' ');      
        }
        
        //temp=result;
        System.out.println(result);
        File file = new File(fileName);

        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file))) {
            for(int i=0;i<result.length();i++){
                bw.write(result.charAt(i));
            }
            bw.newLine();
            //bw.write("This is another line.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
//210041219-task2
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class task2 {
    public static void main(String args[]) {
        try {
            // step1 load the driver class
            Class.forName("oracle.jdbc.driver.OracleDriver");

            // step2 create the connection object
            Connection con = DriverManager.getConnection(
                    "jdbc:oracle:thin:@localhost:1521:xe", "moushi", "1234");

            // step3 create the prepared statement object

            PreparedStatement pStmt = con.prepareStatement (" insert into transactions values (? ,? ,? ,?, ?)") ;
            //actual values are provided
            pStmt.setInt (1 , 10001) ;
            pStmt.setDate(2, java.sql.Date.valueOf("2022-02-12"));
            pStmt.setInt (3 , 2) ;
            pStmt.setInt (4 , 5000) ;
            pStmt.setInt (5 , 1) ;
            pStmt.executeUpdate () ;
            System.out.println("first query inserted");

            pStmt.setInt (1 , 10005) ;
            pStmt.setDate(2, java.sql.Date.valueOf("2022-10-15"));
            pStmt.setInt (3 , 4) ;
            pStmt.setInt (4 , 10000) ;
            pStmt.setInt (5 , 0) ;
            pStmt.executeUpdate () ;
            System.out.println("second query inserted");

            
            }
        catch (Exception e) {
                System.out.println(e);
                System.out.println("not ok");
        }

    }
}

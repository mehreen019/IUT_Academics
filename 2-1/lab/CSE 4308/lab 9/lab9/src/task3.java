//210041219-task3
import java.sql.*;

public class task3 {
    public static void main(String args[]) {
        try {
            // step1 load the driver class
            Class.forName("oracle.jdbc.driver.OracleDriver");

            // step2 create the connection object
            Connection con = DriverManager.getConnection(
                    "jdbc:oracle:thin:@localhost:1521:xe", "moushi", "1234");

            // step3 create the statement object
            Statement stmt = con.createStatement();

            System.out.println("Executing task 3.1:\n");
            String QUERY = "SELECT  * FROM ACCOUNT";
            ResultSet rs = stmt.executeQuery(QUERY);

            //storing meta data from resultset in another variable
            ResultSetMetaData rsmd = rs.getMetaData () ;
            System.out.println("Number of columns in account table: " + rsmd.getColumnCount() + " \nNames of columns in account table:");
            for ( int i = 1; i <= rsmd.getColumnCount () ; i ++) {
                System.out.println ( "NAME: " + rsmd.getColumnName (i) + " TYPE: " + rsmd.getColumnTypeName (i) ) ;
            }

            System.out.println("\nExecuting task 3.2:\n");
            QUERY = "SELECT  * FROM TRANSACTIONS";
            rs = stmt.executeQuery(QUERY);
            rsmd = rs.getMetaData () ;
            System.out.println("Number of columns in transactions table: " + rsmd.getColumnCount() + " \nNames of columns in transactions table:");
            for ( int i = 1; i <= rsmd.getColumnCount () ; i ++) {
                System.out.println ( "NAME: " + rsmd.getColumnName (i) + " TYPE: " + rsmd.getColumnTypeName (i)) ;
            }

            rs.close();

            }
        catch (Exception e) {
                System.out.println(e);
                System.out.println("not ok");
        }

    }
}

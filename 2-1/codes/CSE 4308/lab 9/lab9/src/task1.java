//210041219-task1
import java.sql.*;

public class task1 {
    public static void main(String args[]) {
        try {
            // step1 load the driver class
            Class.forName("oracle.jdbc.driver.OracleDriver");

            // step2 create the connection object
            Connection con = DriverManager.getConnection(
                    "jdbc:oracle:thin:@localhost:1521:xe", "moushi", "1234");

            // step3 create the statement object
            Statement stmt = con.createStatement();

            System.out.println("\nExecuting task 1.1:\n");
            //writing a query
            String QUERY = "SELECT COUNT(A_ID) AS ID FROM ACCOUNT";
            //storing results from that query in a resultset
            ResultSet rs = stmt.executeQuery(QUERY);
            while (rs.next()) {
                // Display results column by column from resultset
                System.out.print("Total number of accounts: " + rs.getInt("ID") + "\n");
            }
            rs.close();

            System.out.println("\nExecuting task 1.2:\n");
            QUERY = "SELECT COUNT(A_ID) AS id\r\n" + //
                    "FROM ACCOUNT A\r\n" + //
                    "WHERE A_ID IN (\r\n" + //
                    "    SELECT A_ID\r\n" + //
                    "    FROM TRANSACTIONS\r\n" + //
                    "    GROUP BY A_ID\r\n" + //
                    "    HAVING SUM(AMOUNT) > 5000000\r\n" + //
                    ")";
            rs = stmt.executeQuery(QUERY);
            while (rs.next()) {
                // Display values
                System.out.print("CIP COUNT: " + rs.getInt("ID") + "\n");
            }
            rs.close();

            System.out.println("\nExecuting task 1.3:\n");
            QUERY = "SELECT COUNT(A_ID) AS id\r\n" + //
                    "FROM ACCOUNT A\r\n" + //
                    "WHERE A_ID IN (\r\n" + //
                    "    SELECT A_ID\r\n" + //
                    "    FROM TRANSACTIONS\r\n" + //
                    "    GROUP BY A_ID\r\n" + //
                    "    HAVING SUM(AMOUNT) > 2500000 and SUM(AMOUNT) < 4500000\r\n" + //
                    ")";
            rs = stmt.executeQuery(QUERY);
            while (rs.next()) {
                // Display values
                System.out.print("VIP COUNT: " + rs.getInt("ID") + "\n");
            }
            rs.close();

            System.out.println("\nExecuting task 1.4:\n");
            QUERY = "SELECT COUNT(A_ID) AS id\r\n" + //
                    "FROM ACCOUNT A\r\n" + //
                    "WHERE A_ID IN (\r\n" + //
                    "    SELECT A_ID\r\n" + //
                    "    FROM TRANSACTIONS\r\n" + //
                    "    GROUP BY A_ID\r\n" + //
                    "    HAVING SUM(AMOUNT) < 1000000\r\n" + //
                    ")";
            rs = stmt.executeQuery(QUERY);
            while (rs.next()) {
                // Display values
                System.out.print("ORDINARY COUNT: " + rs.getInt("ID") + "\n");
            }
            rs.close();

            System.out.println("\nExecuting task 1.5:\n");
            QUERY = "SELECT COUNT(A_ID) AS id\r\n" + //
                    "FROM ACCOUNT A\r\n" + //
                    "WHERE A_ID IN (\r\n" + //
                    "    SELECT A_ID\r\n" + //
                    "    FROM TRANSACTIONS\r\n" + //
                    "    GROUP BY A_ID\r\n" + //
                    "    HAVING (SUM(AMOUNT) >= 1000000 AND SUM(AMOUNT) <= 2500000) OR (SUM(AMOUNT) >= 4500000 AND SUM(AMOUNT) <= 5000000) \r\n" + //
                    ")";
            rs = stmt.executeQuery(QUERY);
            while (rs.next()) {
                // Display values
                System.out.print("Uncategorized: " + rs.getInt("ID") + "\n");
            }
            rs.close();

            }
        catch (Exception e) {
                System.out.println(e);
                System.out.println("not ok");
        }

    }
    
}

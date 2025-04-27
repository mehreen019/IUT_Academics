import java.sql.*;

class jdbc_practice {
    public static void main(String args[]) {
        try {
            // step1 load the driver class
            Class.forName("oracle.jdbc.driver.OracleDriver");

            // step2 create the connection object
            Connection con = DriverManager.getConnection(
                    "jdbc:oracle:thin:@localhost:1521:xe", "moushi", "1234");

            // step3 create the statement object
            Statement stmt = con.createStatement();

            // step4 execute query
            // drop table
             System.out.println("Drop table...");
            String sql = "DROP TABLE REGISTRATION";
            stmt.executeUpdate(sql);
            System.out.println("Table deleted in given database...");

            // create table
            String sql1 = "CREATE TABLE REGISTRATION " +
                    "(id INTEGER not NULL, " +
                    " first VARCHAR(255), " +
                    " last VARCHAR(255), " +
                    " age INTEGER, " +
                    " PRIMARY KEY ( id ))";

            stmt.executeUpdate(sql1); 
            System.out.println("Created table in given database...");

            // insert table
            System.out.println("Inserting records into the table...");
            String sql2 = "INSERT INTO Registration VALUES (100, 'Zara', 'Ali', 18)";
            stmt.executeUpdate(sql2);
            sql2 = "INSERT INTO Registration VALUES (101, 'Mahnaz', 'Fatma', 25)";
            stmt.executeUpdate(sql2);
            sql2 = "INSERT INTO Registration VALUES (102, 'Zaid', 'Khan', 30)";
            stmt.executeUpdate(sql2);
            sql2 = "INSERT INTO Registration VALUES(103, 'Sumit', 'Mittal', 28)";
            stmt.executeUpdate(sql2);
            System.out.println("Inserted records into the table...");

            // select table
            System.out.println("Selecting records from the table...");
            String QUERY = "SELECT id, first, last, age FROM Registration";
            ResultSet rs = stmt.executeQuery(QUERY);
            while (rs.next()) {
                // Display values
                System.out.print("ID: " + rs.getInt("id"));
                System.out.print(", Age: " + rs.getInt("age"));
                System.out.print(", First: " + rs.getString("first"));
                System.out.println(", Last: " + rs.getString("last"));
            }
            rs.close();

            // update table
            System.out.println("Updating records from the table...");
            String sql3 = "UPDATE Registration " +
                    "SET age = 30 WHERE id in (100, 101)";
            stmt.executeUpdate(sql3);
            String QUERY2 = "SELECT id, first, last, age FROM Registration";
            ResultSet rs1 = stmt.executeQuery(QUERY2);
            while (rs1.next()) {
                // Display values
                System.out.print("ID: " + rs1.getInt("id"));
                System.out.print(", Age: " + rs1.getInt("age"));
                System.out.print(", First: " + rs1.getString("first"));
                System.out.println(", Last: " + rs1.getString("last"));
            }
            rs1.close();

            // delete table
            System.out.println("deleting records from the table...");
            String sql4 = "DELETE FROM Registration " +
                    "WHERE id = 101";
            stmt.executeUpdate(sql4);
            String QUERY3 = "SELECT id, first, last, age FROM Registration";
            ResultSet rs2 = stmt.executeQuery(QUERY3);
            while (rs2.next()) {
                // Display values
                System.out.print("ID: " + rs2.getInt("id"));
                System.out.print(", Age: " + rs2.getInt("age"));
                System.out.print(", First: " + rs2.getString("first"));
                System.out.println(", Last: " + rs2.getString("last"));
            }
            rs2.close();

            // step5 close the connection object
            
            con.close();

        } catch (Exception e) {
            System.out.println(e);
            System.out.println("not ok");
        }

    }
}




// Scanner scanner = new Scanner(System.in);

// System.out.print("Enter your last name: ");
// String lastName = scanner.nextLine();

// System.out.print("Enter your first name: ");
// String firstName = scanner.nextLine();

// System.out.print("Enter your email: ");
// String email = scanner.nextLine();


 	// // 2. Create a statement
	// String sql = "insert into employees "
	// 		+ " (last_name, first_name, email)" + " values (?, ?, ?)";

	// myStmt = myConn.prepareStatement(sql);

	// // set param values
	// myStmt.setString(1, lastName);
	// myStmt.setString(2, firstName);
	// myStmt.setString(3, email);

	// // 3. Execute SQL query
	// myStmt.executeUpdate();

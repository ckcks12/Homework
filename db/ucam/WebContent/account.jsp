<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%!
 
public class Account
{
	int id;
	String pw;
	int is_student;
	String name;
	String email;


	public ArrayList<Account> get()
	{
		try
		{ 
			ArrayList<Account> return_list = new ArrayList<Account>();
			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
			Statement stmt;
			
			stmt = con.createStatement();
			ResultSet rs;
			rs = stmt.executeQuery("select * from account"); 

			while(rs.next())
			{
				Account t = new Account();
				t.id = rs.getInt("id");
				t.pw = rs.getString("pw");
				t.is_student = rs.getInt("is_student");
				t.name = rs.getString("name");
				t.email = rs.getString("email");
				return_list.add(t);
			}

			return return_list;
		}	
		catch(Exception ex)
		{
			return null;
		}
	}

		public boolean put(Account acc)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("insert into account values(" 
										+ acc.id + ", " 
										+ "'" + acc.pw + "', " 
										+ acc.is_student + ", "
										+ "'" + acc.name + "', " 
										+ "'" + acc.email + "')"); 
			if( rslt > 0 )
			{
				return true;
			}
			else
			{
				return false;
			}
		}	
		catch(Exception ex)
		{
			return false;
		}
	}

	public boolean delete(Account acc)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("delete from account where id =" + acc.id); 
			if( rslt > 0 )
			{
				return true;
			}
			else
			{
				return false;
			}
		}	
		catch(Exception ex)
		{
			return false;
		}
	}

}

%>
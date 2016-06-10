<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%!
 
public class Course_Registration
{
	String course_no;
	int s_id;
public ArrayList<Course_Registration> get()
	{
		try
		{ 
			ArrayList<Course_Registration> return_list = new ArrayList<Course_Registration>();
			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			Statement stmt;
			
			stmt = con.createStatement();
			ResultSet rs;
			rs = stmt.executeQuery("select * from course_registration"); 

			while(rs.next())
			{
				Course_Registration t = new Course_Registration();
				t.course_no = rs.getString("course_no");
				t.s_id = rs.getInt("s_id");
				return_list.add(t);
			}

			return return_list;
		}	
		catch(Exception ex)
		{
			return null;
		}
	}
		public boolean put(Course_Registration course_R)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("insert into course_registration values(" 
										+ course_R.s_id + ", " 
										+ course_R.course_no +")"); 
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

	public  boolean delete(Course_Registration course_R)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
//			rslt = stmt.executeUpdate("delete from course_registration where course_no = '" 
												//+course_R.course_no + "' and s_id ="
												//+ course_R.s_id); 
			rslt = stmt.executeUpdate("delete from course_registration where course_no="+course_R.course_no);
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
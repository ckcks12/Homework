<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%!
 
public class Course_Plan
{
	String course_no;
	int course_count;
	String course_text;
public ArrayList<Course_Plan> get()
	{
		try
		{ 
			ArrayList<Course_Plan> return_list = new ArrayList<Course_Plan>();
			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			Statement stmt;
			
			stmt = con.createStatement();
			ResultSet rs;
			rs = stmt.executeQuery("select * from course_plan"); 

			while(rs.next())
			{
				Course_Plan t = new Course_Plan();
				t.course_no = rs.getString("course_no");
				t.course_count = rs.getInt("course_count");
				t.course_text = rs.getString("course_text");

				return_list.add(t);
			}

			return return_list;
		}	
		catch(Exception ex)
		{
			return null;
		}
	}

	public boolean put(Course_Plan cour)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("insert into course_plan values(" 
										+ "'" + cour.course_no + "', " 
										+ cour.course_count + ", " 
										+ "'"+cour.course_text + "')"); 
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

	public boolean delete(Course_Plan cour)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("delete from course_plan where course_no =" + cour.course_no); 
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

	public boolean update(Course_Plan cour)
	{
		try
		{
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");

			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("update course_plan set "
										+ "course_no = " + cour.course_no + ", "
										+ "course_count = " + cour.course_count + ", "
										+ "course_text = " + cour.course_text +  " "
										+ "where course_no = " + cour.course_no); 
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

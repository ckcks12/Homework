<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%!
 
public class Course
{
	String course_no;
	int p_id;
	String name;
	int open_year;
	int semester;
	int max_s;
public  ArrayList<Course> get() 
	{
		try
		{ 
			ArrayList<Course> return_list = new ArrayList<Course>();
			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/miniucam", "eunju", "eunju");
	      
			Statement stmt;
			
			stmt = con.createStatement();
			ResultSet rs;
			rs = stmt.executeQuery("select * from course"); 

			while(rs.next())
			{
				Course t = new Course();
				t.course_no = rs.getString("course_no");
				t.p_id = rs.getInt("p_id");
				t.name = rs.getString("name");
				t.open_year = rs.getInt("open_year");
				t.semester = rs.getInt("semester");
				t.max_s = rs.getInt("max_s");
				return_list.add(t);
			}

			return return_list;
		}	
		catch(Exception ex)
		{

			return null;
		}
	}

	public  boolean put(Course cour)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("insert into course values(" 
										+ "'" + cour.course_no +"', " 
										+ cour.p_id + ", " 
										+ "'"+cour.name +"', "
										+cour.open_year+", "
										+ cour.semester+", "
										+cour.max_s + ")"); 
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

	public  boolean delete(Course cour)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("delete from course where course_no =" + cour.course_no); 
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

	public  boolean update(Course cour)
	{
		try
		{
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");

			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("update course set "
										+ "p_id = " + cour.p_id + ", "
										+ "name = " + cour.name + ", "
										+ "semester = " + cour.semester + ", "
										+ "open_year = " + cour.open_year + ", "
										+ "max_s = " + cour.max_s + " "
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
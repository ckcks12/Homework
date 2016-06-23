<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%!
 
public class Board
{
	int pk;
	String course_no;
	String title;
	String attach1;
	String attach2;
	int p_id;
	int timestamp;
	public ArrayList<Board> get()
	{
		try
		{ 
			ArrayList<Board> return_list = new ArrayList<Board>();
			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			Statement stmt;
			
			stmt = con.createStatement();
			ResultSet rs;
			rs = stmt.executeQuery("select * from board"); 

			while(rs.next())
			{
				Board t = new Board();
				t.pk = rs.getInt("pk");
				t.course_no = rs.getString("course_no");
				t.title = rs.getString("title");
				t.attach1 = rs.getString("attach1");
				t.attach2 = rs.getString("attach2");
				t.p_id = rs.getInt("p_id");
				//t.timestamp = rs.getInt("timestamp");
				return_list.add(t);
			}

			return return_list;
		}	
		catch(Exception ex)
		{
			return null;
		}
	}
	public boolean put(Board board)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("insert into board(course_no, title, attach1, attach2, p_id) values('" 
										+ board.course_no + "', '" 
										+ board.title + "', '" 
										+ board.attach1 +"','" 
										+ board.attach2 + "'," 
										+ board.p_id + ")"); 
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

	public boolean delete(Board board)
	{
		try
		{  
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");
	      
			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("delete from board where pk =" + board.pk + " and course_no ="+board.course_no); 
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

	public boolean update(Board board)
		/*  */
	{
		try
		{
			Statement stmt;
			int rslt;

			Class.forName("com.mysql.jdbc.Driver");         
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "eunju", "eunju");

			stmt = con.createStatement(); 
			
			rslt = stmt.executeUpdate("update board set "
										+ "pk = " + board.pk + ", "
										+ "course_no = " + board.course_no + ", "
										+ "title = " + board.title + ", "
										+ "attach1 = " + board.attach1 + ", "
										+ "attach2 = " + board.attach2 + ", "
										+ "where pk = " + board.pk + " "
										+ "and course_no = " + board.course_no); 
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
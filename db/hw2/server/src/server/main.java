package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * @author lec
 *
 */
public class main {

	private final static String DB_USR_ID = "db";
	private final static String DB_USR_PW = "db"; 
	private final static String DB_SERVER_ADDR = "localhost";
	private final static String DB_DB_NAME = "db";
	private final static String SERVER_IP = "121.140.194.45";
	private final static int PORT = 4444;
	public static BufferedReader reader;
	public static PrintWriter writer;
	public final static String DELIMITER = "@@";
	
	public static void main(String[] args) { 
		Socket sck;
		java.net.ServerSocket server;
		Connection con = null; 
		String a_query = "select Fname, Lname from EMPLOYEE, WORKS_ON, PROJECT"
				+ " where EMPLOYEE.Dno = ? and PROJECT.Pname = ?"
				+ " and WORKS_ON.ESsn = EMPLOYEE.Ssn and WORKS_ON.Pno = PROJECT.Pnumber"
				+ " and WORKS_ON.Hours >= ?;";
		String b_query = "select Fname, Lname from EMPLOYEE, DEPENDENT"
				+ " where EMPLOYEE.Ssn = DEPENDENT.ESsn and EMPLOYEE.Fname = DEPENDENT.Dependent_name;";
		String c_query = "select Fname, Lname from EMPLOYEE"
				+ " where EMPLOYEE.Super_Ssn = (select Ssn from EMPLOYEE where Fname = ? and Lname = ?);";
		
		log("server start");
		
		try {
			//db connection
			con = DriverManager.getConnection("jdbc:mysql://" + DB_SERVER_ADDR + "/" + DB_DB_NAME, DB_USR_ID, DB_USR_PW);
			log("db connection : true");
		}
		catch(Exception e)
		{
			log("db connection : false");
			e.printStackTrace();
			return;
		}
		
		try {
			server = new ServerSocket(PORT);
		} catch (IOException e1) { 
			e1.printStackTrace();
			return;
		}
		
		while( true )
		{
			try 
			{
				log("waiting for new connection...");
				sck = server.accept();
				sck.setTcpNoDelay(true);
				reader = new BufferedReader(new InputStreamReader(sck.getInputStream()));
				writer = new PrintWriter(sck.getOutputStream());
				
				String str = receive(sck);
				if( str == null )
				{
					log("receive null");
					continue;
				}
				
				str.replace("\n", "");
				String[] str_arr = str.split(DELIMITER);
				for( int i = 0; i<str_arr.length; i++ )
					System.out.println( i + " : " + str_arr[i]);
				if(str_arr.length <= 0 )
				{
					log("wrong format form wff ... kkk");
					continue;
				}
				System.out.println(str);
				
				PreparedStatement stmt;
				if( str_arr[0].equals("a") ) 
				{
					stmt = con.prepareStatement(a_query);
					stmt.setInt(1,  Integer.parseInt(str_arr[1]));
					stmt.setString(2, str_arr[2]);
					stmt.setInt(3, Integer.parseInt(str_arr[3]));
				}else if( str_arr[0].equals("b") )
				{
					stmt = con.prepareStatement(b_query);
				}else if( str_arr[0].equals("c"))
				{
					stmt = con.prepareStatement(c_query);
					stmt.setString(1, str_arr[1]);
					stmt.setString(2, str_arr[2]);
				}
				else
				{
					log("unknown query type");
					continue;
				}
				
				ResultSet rslt = stmt.executeQuery();
				
				String rslt_str = "";
				while( rslt.next() )
				{
					rslt_str += rslt.getString(1) + " " + rslt.getString(2) + DELIMITER;
				}
				
				send(sck, rslt_str);
				sck.close();
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}

	public static void log(String str)
	{
		Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        System.out.println(sdf.format(cal.getTime()) + " : " + str);
	}

	public static String receive(Socket sck)
	{ 
		String tmp, str;
		str = "";
		
		log("receive start"); 
		
		try {
			return reader.readLine();
		} catch (IOException e1) {
			log("an error occured while reader read lines");
			e1.printStackTrace();
			return null;
		} 
	}
	
	public static void send(Socket sck, String str)
	{  
		log("send start\n" + str);
		
		try {
			sck.setTcpNoDelay(true);
			
		} catch (IOException e) {
			log("cannot create print writer from socket");
			e.printStackTrace();
			return;
		}
		
		writer.println(str);
		writer.flush();  
		
		return;
	}
}

/*
Connection con = null;

try {
				
	
	String q = "show tables;";
	PreparedStatement stmt = con.prepareStatement(q);
	ResultSet rslt = null;
	
	stmt.execute();
	
	rslt = stmt.getResultSet();
	
	while(rslt.next()){
		System.out.println(rslt.getString(1));
	}
	
} catch (SQLException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
}
*/
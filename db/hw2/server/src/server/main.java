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
	private final static int PORT = 1212;
	public static BufferedReader reader;
	public static PrintWriter writer;
	public final static String DELIMITER = "@@";
	
	public static void main(String[] args) { 
		Socket sck;
		java.net.ServerSocket server;
		Connection con = null; 
		// below string variables are for preparestatements.
		// PrepareStatment makes the query be interactive to its input.  
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
			// listen
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
				// block itself until user connect
				sck = server.accept();
				// I will not use Nagle's algorithm.. 
				sck.setTcpNoDelay(true);
				reader = new BufferedReader(new InputStreamReader(sck.getInputStream()));
				writer = new PrintWriter(sck.getOutputStream());
				
				// at first, read from client. 
				String str = receive(sck);
				if( str == null )
				{
					log("receive null");
					continue;
				}
				
				// unpacking process... :) the packet is sent by one by \n. 
				str.replace("\n", "");
				String[] str_arr = str.split(DELIMITER);
				// debugging its input from client
				for( int i = 0; i<str_arr.length; i++ )
					System.out.println( i + " : " + str_arr[i]);
				if(str_arr.length <= 0 )
				{
					log("wrong format form wff ... kkk");
					continue;
				}
				System.out.println(str);
				
				// first part of the packet is the type of which query will be executed
				// according to textbook's Exercises
				// and by the feature of prepareStatment, it will be replaced as client's input.
				// so that the query can bring appropriate result to the client.
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
				
				// submit the query, I mean execute it.
				ResultSet rslt = stmt.executeQuery();
				
				// and read query's results by column index.
				// because of the equivalence of the number of its result's columns
				// we can assume that only two columns are all what we need.
				String rslt_str = "";
				while( rslt.next() )
				{
					rslt_str += rslt.getString(1) + " " + rslt.getString(2) + DELIMITER;
				}
				
				// send the result. 
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

	/*
	 * receive from socket. just one line per each its execution
	 */
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
	
	/*
	 * send string to socket. never use Nagle's one. never and ever.
	 * because sometimes string that will be sent is too short 
	 * so that Nagle prevent it from being sent.
	 */
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
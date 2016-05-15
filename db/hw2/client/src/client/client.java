package client;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.Socket;
import java.net.SocketAddress;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Scanner;

public class client {
	
	private final static String SERVER_IP = "121.140.194.45";
	private final static int PORT = 4444;
	public static BufferedReader reader;
	public static PrintWriter writer;
	public final static String DELIMITER = "@@";
	
	public static void main(String[] args) {
		 Socket sck;
		 int query_type = 0;
		 String str = "";
		 Scanner in = new Scanner(System.in); 
		 
		 System.out.println("which problem do you want to execute?");
		 System.out.println("1. a");
		 System.out.println("2. b");
		 System.out.println("3. c");
		  
		 query_type = in.nextInt();
		 in.nextLine();
		 
		 if( query_type == 1 )
		 {
			 str = "a" + DELIMITER;
			 System.out.println("몇번부서?");
			 str += in.nextLine() + DELIMITER;
			 System.out.println("무슨 프로젝트?");
			 str += in.nextLine() + DELIMITER;
			 System.out.println("몇시간 이상?");
			 str += in.nextLine() + DELIMITER;
		 }
		 else if(query_type == 2)
		 {
			 str = "b" + DELIMITER;
		 }
		 else if(query_type == 3)
		 {
			 str = "c" + DELIMITER;
			 System.out.println("누구? (직접관리하는 사람 이름)");
			 String tmp = in.nextLine();
			 str += tmp.split(" ")[0] + DELIMITER;
			 str += tmp.split(" ")[1] + DELIMITER;
		 }
		 		 
		 try
		 {
			 sck = new Socket(SERVER_IP, PORT);
			 reader = new BufferedReader(new InputStreamReader(sck.getInputStream()));
			 writer = new PrintWriter(sck.getOutputStream());
			 send(sck, str);
			 System.out.println("결과값");
			 String[] str_arr = receive(sck).split(DELIMITER);
			 for( int i=0; i<str_arr.length; i++ )
			 {
				 System.out.println(str_arr[i]);
			 }
		 }catch(Exception e)
		 {
			 e.printStackTrace();
		 }
		 
	}
 
	public static String receive(Socket sck)
	{ 
		String tmp, str;
		str = "";
		
		//log("receive start"); 
		
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
		//log("send start\n" + str);
		
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
	
	public static void log(String str)
	{
		Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        System.out.println(sdf.format(cal.getTime()) + " : " + str);
	}
}

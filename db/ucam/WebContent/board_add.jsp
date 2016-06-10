<%@page import="java.nio.file.Path"%>
<%@page import="java.io.FileOutputStream"%>
<%@page import="org.apache.tomcat.util.http.fileupload.FileUtils"%>
<%@page import="java.io.OutputStreamWriter"%>
<%@page import="java.io.OutputStream"%>
<%@page import="java.io.FileInputStream"%>
<%@page import="java.nio.file.Paths"%>
<%@page import="java.nio.file.Files"%>
<%@page import="org.apache.tomcat.util.http.fileupload.IOUtils"%>
<%@page import="java.io.BufferedReader"%>
<%@page import="java.nio.CharBuffer"%>
<%@page import="java.io.FileReader"%>
<%@ page pageEncoding="UTF-8" %> 
<%@include file="menu.jsp" %> 
<%@page import="java.io.File"%>
<%@page import="com.oreilly.servlet.multipart.DefaultFileRenamePolicy"%>
<%@page import="com.oreilly.servlet.MultipartRequest"%> 
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<title></title>
		<style></style>
		<script type="text/javascript"></script>
	</head>

	<body>
	
<%
	String saveDir = application.getRealPath("upload"); 
	int maxSize = 1024*1024*100;
	String encType = "UTF-8";

	MultipartRequest multipartRequest
	= new MultipartRequest(request, saveDir, maxSize, encType, new DefaultFileRenamePolicy());
	
	Board b = new Board();
	b.course_no = multipartRequest.getParameter("course_no");
	b.title = multipartRequest.getParameter("title");
	b.attach1 = multipartRequest.getFilesystemName("attach1");
	if( b.attach1 == null )
	{
		b.attach1 = "";
	}
	b.attach2 = multipartRequest.getFilesystemName("attach2");
	if( b.attach2 == null )
	{
		b.attach2 = "";
	}
    b.p_id = Integer.parseInt(session.getAttribute("id").toString());
    
	File file;
	int len;
	byte[] bb; 
    if( b.attach1.length() > 2 )
    {
    	file = multipartRequest.getFile("attach1");
        len = (int)file.length();
        bb = new byte[len];
        new FileInputStream(file).read(bb);
		Files.write(Paths.get(saveDir + "\\" + b.attach1), bb);
    }
     
    if( b.attach2 != null && b.attach2.length() > 2 )
    {
    	file = multipartRequest.getFile("attach2");
        len = (int)file.length();
        bb = new byte[len];
        new FileInputStream(file).read(bb);
		Files.write(Paths.get(saveDir + "\\" + b.attach2), bb);
    } 
    
    Boolean success = false;
    if( b.put(b) )
    {
    	success = true;
    }
%>

	<% 
        if( success )
        {
            response.sendRedirect("board_list_view.jsp?course_no=" + multipartRequest.getParameter("course_no"));
        }
        else
        {
        	out.println(b.p_id);
            //out.println(alertToBack("글쓰기에 실패하였습니다"));
        }
    %>
	</body>
</html>
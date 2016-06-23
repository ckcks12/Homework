<%@page import="java.io.FileInputStream"%>
<%@page import="java.nio.file.Paths"%>
<%@page import="java.nio.file.Files"%>
<%@page import="org.apache.tomcat.util.http.fileupload.IOUtils"%>
<%@page import="java.io.BufferedReader"%>
<%@page import="java.nio.CharBuffer"%>
<%@page import="java.io.FileReader"%>
<%@ page pageEncoding="UTF-8" %>
<%@include file="account.jsp" %>
<%@include file="board.jsp" %>
<%@include file="course.jsp" %>
<%@include file="course_registration.jsp" %>
<%@include file="course_plan.jsp" %>
<%@include file="tool.jsp" %>  
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
	
    out.write("이름 : " + multipartRequest.getParameter("name") + "<br>");
    out.write("파일 : " + multipartRequest.getParameter("file") + "<br>"); //null 값을 갖는다.
    out.write("업로드파일명 : " + multipartRequest.getFilesystemName("file") + "<br>");
    out.write("원래파일명 : " + multipartRequest.getOriginalFileName("file") + "<br>");
    
    File file = multipartRequest.getFile("file");
    byte[] b = new byte[(int)file.length()];
    new FileInputStream(file).read(b);
    
    for( int i=0; i<b.length; i++ )
    {
    	out.println(i + " : " + (int)b[i] + "<br/>");
    }
%>

	파일용량 : <fmt:formatNumber value="<%=file.length() %>" groupingUsed="true"/>

	</body>
</html>
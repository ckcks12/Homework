<%@ page pageEncoding="UTF-8" %>
<%@ page import="java.io.*" %>
<%@ page import="java.sql.*" %>

<!DOCTYPE html>
<head>
	<meta charset="utf-8">
</head>
<body> 

<%
Class.forName("com.mysql.jdbc.Driver");         
Connection con = DriverManager.getConnection("jdbc:mysql://localhost/miniucam", "root", "root");
%>  

</body>
</html> 
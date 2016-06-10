<%@ page pageEncoding="UTF-8" %>
<%@include file="account.jsp" %>
<%@include file="board.jsp" %>
<%@include file="course.jsp" %>
<%@include file="course_registration.jsp" %>
<%@include file="course_plan.jsp" %>
<%@include file="tool.jsp" %>

<!DOCTYPE html>
<html>
<head>
    <title></title>
</head>
<body>
<form action="upload.jsp" method="post" enctype="multipart/form-data">
	이름 : <input type="text" name="name"><br>
	파일 : <input type="file" name="file"><br>
	<input type="submit" name="업로드"><br>
</form>
</body>
</html>
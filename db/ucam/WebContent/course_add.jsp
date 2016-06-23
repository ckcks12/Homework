<%@ page pageEncoding="UTF-8" %>
<%@include file="menu.jsp"%>

<%
	Boolean success = false;

    Course cour = new Course();
	cour.course_no = request.getParameter("course_no");
	cour.p_id = Integer.parseInt(session.getAttribute("id").toString());
	cour.name = request.getParameter("name");
	cour.open_year = Integer.parseInt((request.getParameter("open_year")));
	cour.semester = Integer.parseInt(request.getParameter("semester"));
	cour.max_s = Integer.parseInt(request.getParameter("max_s"));
	
	if( cour.put(cour) ) 
	{
		success = true;
	}
	
%>

<!DOCTYPE html>
<html>
<head>
    <title></title>
</head>
<body>
    <% 
        if( success )
        {
            response.sendRedirect("course_view.jsp");
        }
        else
        {
            out.println(alertToBack("강의 추가에 실패하였습니다"));
        }
    %>
</body>
</html>
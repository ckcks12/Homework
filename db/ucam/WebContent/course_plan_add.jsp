<%@ page pageEncoding="UTF-8" %>
<%@include file="menu.jsp"%>

<%
	Boolean success = false;
	
	Course_Plan plan = new Course_Plan();
	
	plan.course_no = request.getParameter("course_no");
	plan.course_text = request.getParameter("course_text");
	plan.course_count = 0;
	
	if( plan.put(plan) ) 
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
            response.sendRedirect("course_plan_view.jsp?course_no="+request.getParameter("course_no"));
        }
        else
        {
            out.println(alertToBack("강의계획서 작성에 실패하였습니다"));
        }
    %>
</body>

<%@ page pageEncoding="UTF-8" %>
<%@include file="menu.jsp"%>

<%
	Boolean success = false;
	
	Course_Registration reg = new Course_Registration();
	
	reg.s_id = Integer.parseInt(session.getAttribute("id").toString());
	reg.course_no = request.getParameter("course_no");
    
	if( reg.put(reg) ) 
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
            out.println(alertToBack("수강 신청에 실패하였습니다"));
        }
    %>
</body>

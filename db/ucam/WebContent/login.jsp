<%@ page pageEncoding="UTF-8" %>
<%@include file="account.jsp" %>
<%@include file="board.jsp" %>
<%@include file="course.jsp" %>
<%@include file="course_registration.jsp" %>
<%@include file="course_plan.jsp" %>
<%@include file="tool.jsp" %>

<%
    Account acc = new Account();
    ArrayList<Account> acc_list = new ArrayList<Account>();
    String id = request.getParameter("id");
    String pw = request.getParameter("pw");
    String error;
    Boolean success = false;

    acc_list = acc.get();
    if( acc_list != null )
    {
        for( Account a : acc_list )
        {
            if( String.valueOf(a.id).equals(id)
                && a.pw.equals(pw) )
            {
                success = true;
                session.setAttribute("id", id);
                session.setAttribute("is_student", a.is_student);
                session.setAttribute("name", a.name);
                break;
            }
        }
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
            response.sendRedirect("main.jsp");
        }
        else
        {
            out.println(alertToBack("로그인에 실패하였습니다"));
        }
    %>
</body>
</html>
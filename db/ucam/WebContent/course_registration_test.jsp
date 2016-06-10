<%@ page pageEncoding="EUC-KR" %>
<%@include file="course_registration.jsp" %>

<!DOCTYPE html>
<head>
	<meta charset="euc-kr">
</head>
<body> 
 
<% 
	Course_Registration r = new Course_Registration(); 

   ArrayList<Course_Registration> r_list = new ArrayList<Course_Registration>();

   // acc_list = acc.get(); 
   // for( Course_Registration a : r_list )
   // {
   //    out.println(a.id + ", " + a.name);
   //    out.println("<br/>");
   // }

	r.course_no = "333892";
   r.s_id = 9876;
    if( r.put(r) )
    {
       out.println("true!!!");
    }
    else
    {
       out.println("false!!!");
    }
   out.println("<br/>");
   if(r.delete(r))
      {
out.println("yes!");
}
else
out.println("bbb");
   r_list = r.get(); 
   for( Course_Registration a : r_list )
   {
      out.println(a.course_no + ", " + a.s_id);
      out.println("<br/>");
   } 

%>  

</body>
</html> 
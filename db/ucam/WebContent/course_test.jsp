<%@ page pageEncoding="EUC-KR" %>
<%@include file="course.jsp" %>

<!DOCTYPE html>
<head>
   <meta charset="euc-kr">
</head>
<body> 
 
<% 
   Course course = new Course(); 

   ArrayList<Course> course_list = new ArrayList<Course>();

   course_list = course.get(); 
   for( Course c : course_list )
   {
      out.println(c.p_id + ", " + c.open_year);
      out.println("<br/>");
   }

   course.course_no = "3030882";
   course.p_id = 8;
   course.open_year = 2016;
   course.semester = 1;
   course.name = "software";
   course.max_s = 44;
   if( course.put(course) )
   {
      out.println("true!!!");
   }
   else
   {
      out.println("false!!!");
   }
   out.println("<br/>");

   if( course.delete(course) )
   {
         out.println("delete_true!!!");
   }
   else
   {
         out.println("delete_false!!!");
   }

   course_list = course.get(); 
   for( Course a : course_list )
   {
      out.println(a.course_no + ", " + a.p_id);
      out.println("<br/>");
   } 

%>  

</body>
</html> 
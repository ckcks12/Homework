<%@ page pageEncoding="EUC-KR" %>
<%@include file="course_plan.jsp" %>

<!DOCTYPE html>
<head>
   <meta charset="euc-kr">
</head>
<body> 
 
<% 
   Course_Plan course_plan = new Course_Plan(); 

   ArrayList<Course_Plan> course_plan_list = new ArrayList<Course_Plan>();

   course_plan_list = course_plan.get(); 
   for( Course_Plan a : course_plan_list )
   {
      out.println(a.course_no + ", " + a.course_count);
      out.println("<br/>");
   } 

   course_plan.course_no = "1111111";
   course_plan.course_count = 20;
   course_plan.course_text = "hohojjhhhee ";
   if( course_plan.put(course_plan) )
   {
      out.println("true!!!");
   }
   else
   {
      out.println("false!!!");
   }
   out.println("<br/>");

   // if( course_plan.delete(course_plan) )
   // {
   //       out.println("delete_true!!!");
   // }
   // else
   // {
   //       out.println("delete_false!!!");
   // }

   course_plan_list = course_plan.get(); 
   for( Course_Plan a : course_plan_list )
   {
      out.println(a.course_no + ", " + a.course_count);
      out.println("<br/>");
   } 

%>  

</body>
</html> 
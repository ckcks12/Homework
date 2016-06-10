<%@ page pageEncoding="EUC-KR" %>
<%@include file="account.jsp" %>

<!DOCTYPE html>
<head>
	<meta charset="euc-kr">
</head>
<body> 
 
<% 
	Account acc = new Account(); 

   ArrayList<Account> acc_list = new ArrayList<Account>();

   acc_list = acc.get(); 
   for( Account a : acc_list )
   {
      out.println(a.id + ", " + a.name);
      out.println("<br/>");
   }

	acc.id = 10;
   acc.is_student = 1;
   acc.pw = "1";
   acc.name = "leechan";
   acc.email = "abc@hhoh.com";
   if( acc.put(acc) )
   {
      out.println("true!!!");
   }
   else
   {
      out.println("false!!!");
   }
   out.println("<br/>");

   acc_list = acc.get(); 
   for( Account a : acc_list )
   {
      out.println(a.id + ", " + a.name);
      out.println("<br/>");
   } 

%>  

</body>
</html> 
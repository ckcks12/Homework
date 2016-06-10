<%@ page pageEncoding="EUC-KR" %>
<%@include file="board.jsp" %>

<!DOCTYPE html>
<head>
   <meta charset="euc-kr">
</head>
<body> 
 
<% 
   Board board = new Board(); 

   ArrayList<Board> board_list = new ArrayList<Board>();

   board_list = board.get(); 
   for( Board b : board_list )
   {
      out.println(b.pk + ", " + b.title);
      out.println("<br/>");
   }
   String str1 = "gegegege";
   board.course_no = "23456";
   board.title = "wwwwwww";
   board.attach1 = "1";
   board.attach2 = "1";
   board.p_id = 4567;

   if( board.put(board) )
   {
      out.println("true!!!");
   }
   else
   {
      out.println("false!!!");
   }
   out.println("<br/>");

   // if( board.delete(board) )
   // {
   //       out.println("delete_true!!!");
   // }
   // else
   // {
   //       out.println("delete_false!!!");
   // }

   board_list = board.get(); 
   //out.println(board_list);
   
   for( Board b : board_list )
   {
      out.println(b.pk + ", " + b.title);
      out.println("<br/>");
   }
%>  

</body>
</html> 
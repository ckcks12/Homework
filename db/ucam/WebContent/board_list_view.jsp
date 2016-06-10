<%@ page pageEncoding="UTF-8" %> 
<%@include file="menu.jsp" %> 

<%
	ArrayList<Board> board_list2 = new ArrayList<Board>();

	for( Board b : board_list )
	{
		if( b.course_no.equals(request.getParameter("course_no")) )
		{
			board_list2.add(b);
		}
	}
%>

<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.css">
    <style type="text/css">
    </style>
</head>
<body>
    <div class="ui center aligned container">
        <img src="https://info.kw.ac.kr/include/images/logo.gif" alt="" style="margin: 75px auto;">
        <div class="ui grid">
            <div class="row">
                <div class="four wide column">
                    <div class="ui vertical menu">
                        <% for( int i=0; i<menu_list.size(); i++ ) { %>
                            <%="<a href='" + menu_url.get(i) + "' class='item'>" + menu_list.get(i) + "</a>"%>
                        <% } %>
                    </div>
                </div>
                <div class="twelve wide column">
                	<% for( Board b : board_list2 ) { %>
	                    <div class="ui segment">
    	                	<%=b.title%>
    	                	<% if( b.attach1.length() > 2 ) out.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='/ucam/download.jsp?file_name=" + b.attach1 + "'>파일1</a>"); %>
    	                	<% if( b.attach2.length() > 2 ) out.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='/ucam/download.jsp?file_name=" + b.attach2 + "'>파일2</a>"); %>
        	            </div>
					<% } %>
					<br/>
					<br/>
					<% if( Integer.parseInt(session.getAttribute("is_student").toString()) == 1 ) { %>
						<button type="button" class="ui button" onclick="location.href='board_write.jsp?course_no=<%=request.getParameter("course_no")%>';">자료 추가</button>
					<% } %>
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.js"></script>
    <script type="text/javascript"> ript>
</body>
</html>
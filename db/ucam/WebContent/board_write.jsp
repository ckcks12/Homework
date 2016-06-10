<%@ page pageEncoding="UTF-8" %> 
<%@include file="menu.jsp" %> 

<%
	
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
                	<form action="board_add.jsp" method="post" enctype="multipart/form-data" class="ui form">
                		<input type="hidden" name="course_no" value="<%=request.getParameter("course_no")%>">
                		<div class="field">
                			<label>글</label>
                			<input type="text" name="title">
                		</div>
                		<div class="field">
                			<label>첨부1</label>
                			<input type="file" name="attach1">
                		</div>
                		<div class="field">
                			<label>첨부2</label>
                			<input type="file" name="attach2">
                		</div>
                		<button type="submit" class="ui green button">작성</button>
                	</form> 
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.js"></script>
    <script type="text/javascript"> ript>
</body>
</html>
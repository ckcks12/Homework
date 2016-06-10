<%@ page pageEncoding="UTF-8" %> 
<%@include file="menu.jsp" %> 

<%
	ArrayList<Account> acc_list2 = new ArrayList<Account>();
	for( Course_Registration reg : cour_reg_list )
	{
		if( reg.course_no.equals(request.getParameter("course_no")) )
		{
			for( Account acc : acc_list )
			{
				if( acc.id == reg.s_id )
				{
					acc_list2.add(acc);
					break;
				}
			}
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
                	<% for( Account acc : acc_list2 ) { %>
	                    <div class="ui segment">
    	                	<%="학번 : " + acc.id + " 이름 : " + acc.name + " 이메일 : " + acc.email+"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"%>
    	                	<button type="button" class="ui green button" onclick="sendMail('<%=acc.email%>');">메일보내기</button>
        	            </div>
					<% } %> 
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.js"></script>
    <script type="text/javascript">
    function sendMail(email)
    {
    	var html = "mail.jsp?to=" + email + "&title=" + prompt("제목") + "&content=" + prompt("내용");
    	location.href = html;
    }
    </script>
</body>
</html>
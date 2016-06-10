<%@ page pageEncoding="UTF-8" %> 
<%@include file="menu.jsp" %> 

<%
	Course cour = null;
	Account prof = null;
	Course_Plan plan = null;
	
	for( Course c : cour_list )
	{
		if( c.course_no.equals(request.getParameter("course_no")) )
		{
			cour = c;
			
			for( Account acc : acc_list )
			{
				if( cour.p_id == acc.id )
				{
					prof = acc;
					break;
				}
			}
			
			for( Course_Plan p : cour_plan_list )
			{
				if( p.course_no.equals(cour.course_no) )
				{
					plan = p;
					break;
				}
			}
			
			break;
		}
	}
	if( cour == null || prof == null )
	{
		alertToUrl("없는 강의입니다", "/ucam/main.jsp");
	}
	if( plan == null )
	{
		plan = new Course_Plan();
		plan.course_count = 0;
		plan.course_text = "아직 강의 계획서가 없습니다";
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
                	<div class="ui segment">
	                	<h3 class="ui dividing header">강의 계획서</h3>
                		강의 이름 : <%=cour.name%><br/>
                		교수 : <%=prof.name%><br/>
                		교수 이메일 : <%=prof.email%><br/>
                		개설일 : <%=cour.open_year%>년도 <%=cour.semester%>학기<br/>
                		최대 수강 인원 : <%=cour.max_s%><br/> 
                		<br/>
                		<br/>
                		<p><%=plan.course_text%></p>
                	</div>
                	<br/>
                	<br/>
                	<% if( cour.p_id == Integer.parseInt(session.getAttribute("id").toString()) 
                			&& plan.course_text.equals("아직 강의 계획서가 없습니다") ) { %>
                		<button type="button" class="ui button" onclick="coursePlanAdd(<%=cour.course_no%>);">계획서쓰기</button>
                	<% } %>
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.js"></script>
    <script type="text/javascript">
    function coursePlanAdd(course_no)
    {
    	var href = "course_plan_add.jsp?course_no=" + course_no +"&course_text=" + prompt("강의계획내용");
    	location.href = href;
    }
    </script>
</body>
</html>
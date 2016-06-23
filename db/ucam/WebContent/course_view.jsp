<%@ page pageEncoding="UTF-8" %> 
<%@include file="menu.jsp" %> 

<%
	ArrayList<Course> cour_list2 = new ArrayList<Course>();
	for( Course cour : cour_list )
	{
		for( Account acc : acc_list )
		{
			if( cour.p_id == acc.id )
			{
				cour.name += "(" + acc.name + ")";
				break;
			}
		}
		
		if( is_student == 0 )
		{
			cour_list2.add(cour);
		}
		else
		{
			if( cour.p_id == Integer.parseInt(session.getAttribute("id").toString()) )
			{
				cour_list2.add(cour);
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
                	<% for( Course cour : cour_list ) { %>
	                    <div class="ui segment">
    	                	<%="[" + cour.course_no + "] " + cour.name + " " + cour.open_year + "년도 " + cour.semester + "학기" + " 최대 수강 인원 : " + cour.max_s%>
    	                	<br/><br/>
    	                	<% 
    	                		String tmp = "<button type='button' class='ui green button' onclick='courseRegAdd(" + cour.course_no + ");'>수강신청</button>";
    	                		for( Course_Registration reg : cour_reg_list )
    	                		{
    	                			if( cour.course_no.equals(reg.course_no) 
    	                					&& reg.s_id == Integer.parseInt(session.getAttribute("id").toString()) )
    	                			{
    	                				tmp = "<button type='button' class='ui disabled button'>수강중</button>";
    	                				break;
    	                			}
    	                		}
    	                		out.println(tmp);
    	                	%>
        	            </div>
					<% } %>
					<br/>
					<br/>
					<% if( Integer.parseInt(session.getAttribute("is_student").toString()) == 1) { %>
						<button type="button" class="ui button" onclick="courseAdd();">강의 추가</button>
					<% } %>
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.js"></script>
    <script type="text/javascript">
    function courseAdd()
    {
    	var href = "course_add.jsp?course_no=" + prompt("강의번호") +"&name=" + prompt("강의이름") + "&open_year=" + prompt("강의년도")
    				+ "&semester=" + prompt("강의학기") + "&max_s=" + prompt("최대 수강 인원");
    	location.href = href;
    }
    function courseRegAdd(course_no)
    {
    	location.href = "course_reg_add.jsp?course_no=" + course_no;
    }
    </script>
</body>
</html>
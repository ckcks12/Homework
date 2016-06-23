<%@ page pageEncoding="UTF-8" %>
<%@include file="account.jsp" %>
<%@include file="board.jsp" %>
<%@include file="course.jsp" %>
<%@include file="course_registration.jsp" %>
<%@include file="course_plan.jsp" %>
<%@include file="tool.jsp" %>
<%
	ArrayList<Account> acc_list = new Account().get();
	ArrayList<Board> board_list = new Board().get();
	ArrayList<Course_Plan> cour_plan_list = new Course_Plan().get();
	ArrayList<Course_Registration> cour_reg_list = new Course_Registration().get();
	ArrayList<Course> cour_list = new Course().get();
%>
<%
if( String.valueOf(session.getAttribute("id")).length() < 1 )
{
    out.println(alertToUrl("로그인이 필요합니다", "/"));
}

// 학생, 교수 메뉴
int is_student = (Integer)session.getAttribute("is_student");
ArrayList<String> menu_list = new ArrayList<String>(); 
ArrayList<String> menu_url = new ArrayList<String>();
menu_list.add("로그아웃");
menu_url.add("logout.jsp");
if( is_student == 0 )
{
    menu_list.add("수강 관리");
    menu_url.add("course_view.jsp");
    for( Course cour : cour_list )
    {
    	for( Course_Registration reg : cour_reg_list )
    	{
    		if( reg.s_id == Integer.parseInt(session.getAttribute("id").toString()) 
    				&& reg.course_no.equals(cour.course_no) )
    		{
    			menu_list.add(""); menu_url.add("#");
    			menu_list.add(cour.name);
    			menu_url.add("#");
    			menu_list.add("강의계획서");
    			menu_url.add("course_plan_view.jsp?course_no=" + cour.course_no);
    			menu_list.add("강의자료실");
    			menu_url.add("board_list_view.jsp?course_no=" + cour.course_no);
    		}
    	}
    }
}
else
{
    menu_list.add("강의 관리");
    menu_url.add("course_view.jsp");
    for( Course cour : cour_list )
    {
    	if( cour.p_id == Integer.parseInt(session.getAttribute("id").toString()) )
    	{
    		menu_list.add(""); menu_url.add("#");
    		menu_list.add(cour.name);
			menu_url.add("#");
			menu_list.add("수강생관리");
			menu_url.add("student_view.jsp?course_no=" + cour.course_no);
			menu_list.add("강의계획서");
			menu_url.add("course_plan_view.jsp?course_no=" + cour.course_no);
			menu_list.add("강의자료실");
			menu_url.add("board_list_view.jsp?course_no=" + cour.course_no);
    	}
    }
}

%>

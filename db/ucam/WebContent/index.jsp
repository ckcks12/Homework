<%@ page pageEncoding="UTF-8" %>
<%@include file="account.jsp" %>
<%@include file="board.jsp" %>
<%@include file="course.jsp" %>
<%@include file="course_registration.jsp" %>
<%@include file="course_plan.jsp" %>
<%@include file="tool.jsp" %>

<!DOCTYPE html>
<head>
	<meta charset="utf-8">
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.css">
</head>
<body>
	<div class="ui container">
		<div class="ui middle aligned center aligned grid" style="margin-top: 75px;">
			<div class="column" style="max-width: 450px;">
				<img src="https://info.kw.ac.kr/include/images/logo.gif" alt="" style="margin-bottom: 50px;">
				<form action="login.jsp" method="post" class="ui form">
					<input type="hidden" name="to" value="ckcks12@naver.com">
					<div class="ui field">
						<label for="">학번</label>
						<input type="text" name="id">
					</div>
					<div class="ui field">
						<label for="">비밀번호</label>
						<input type="password" name="pw">
					</div>
					<button class="ui inverted brown button">로그인</button>
				</form>
			</div>
		</div>
	</div>
	<script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
	<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.1.8/semantic.min.js"></script>
</body>
</html>
/**
 * draw clock
 */
var canvas = document.getElementById("clock");
var ctx = canvas.getContext("2d");
var radius = canvas.height / 2;
ctx.translate(radius, radius);
radius = radius * 0.90;
setInterval(drawClock, 999); //1000 is not 1 sec. cuz cpu is too busy to set its timer correct. :) I understand him.

function drawClock()
{
	//draw circular-background
	ctx.arc(0, 0, radius, 0, 2 * Math.PI);
	ctx.fillStyle = "white";
	ctx.fill();

	//draw centeral circle point
    ctx.beginPath();
    ctx.arc(0, 0, radius * 0.05, 0, 2 * Math.PI);
    ctx.fillStyle = 'black';
    ctx.fill();

    //draw numbers
    var ang;
    var num;

    ctx.font = radius * 0.15 + "px arial";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    for( num=1; num<13; num++ )
    {
        ang = num * Math.PI / 6;
        ctx.rotate(ang);
        ctx.translate(0, -radius * 0.85);
        ctx.rotate(-ang);
        ctx.fillText(num.toString(), 0, 0);
        ctx.rotate(ang);
        ctx.translate(0, radius * 0.85);
        ctx.rotate(-ang);
    }

    //darw hands
    var hour_hand_width = radius * 0.07,
    	hour_hand_len = radius * 0.6,
    	min_hand_width = radius * 0.06,
    	min_hand_len = radius * 0.7,
    	sec_hand_width = radius * 0.02,
    	sec_hand_len = radius * 0.8;
    var now = new Date(),
    	h = now.getHours(),
    	m = now.getMinutes(),
    	s = now.getSeconds();

    h = h % 12;
    h = (h * Math.PI / 6) + (m * Math.PI / (6 * 60)) + (s * Math.PI / (360 * 60));
    m = (m * Math.PI / 30) + (s * Math.PI / (30 * 60));
    s = (s * Math.PI / 30);

    ctx.beginPath();
    ctx.lineWidth = hour_hand_width;
    ctx.lineCap = "round";
    ctx.moveTo(0, 0);
    ctx.rotate(h);
    ctx.lineTo(0, -hour_hand_len);
    ctx.stroke();
    ctx.rotate(-h);

    ctx.beginPath();
    ctx.lineWidth = min_hand_width;
    ctx.lineCap = "round";
    ctx.moveTo(0, 0);
    ctx.rotate(m);
    ctx.lineTo(0, -min_hand_len);
    ctx.stroke();
    ctx.rotate(-m);

    ctx.beginPath();
    ctx.lineWidth = sec_hand_width;
    ctx.lineCap = "round";
    ctx.moveTo(0, 0);
    ctx.rotate(s);
    ctx.lineTo(0, -sec_hand_len);
    ctx.stroke();
    ctx.rotate(-s);

    ctx.beginPath();
};

/** 
 * change link's href attribute so that it applies its new skin
 */
$
$("#menu a").click(function(e)
{
	var skin_num;

    //if it is github button
    if( $(this).text() == "github" )
    {
        return true;
    }

	skin_num = $(this).attr("data");
	if( ! (1 <= skin_num && skin_num <= 3) )
	{
		alert("잘못된 스킨 번호입니다");
		return false;
	}

	$("link")[1].href = "skin" + skin_num + ".css";
	return;
});
window.onload = () => {
    const canvas = document.getElementById("canvas");
    const context = canvas.getContext("2d");

    drawLetterM(context);
    drawLetterA(context);
    drawLetterC(context);
}
// легко менять коордиаты букв сделать, про трансформации в канвасе
function drawLetterM(context) 
{
    context.fillStyle = "rgb(0, 0, 255)";

    context.fillRect(30, 0, 20, 180);

    context.beginPath();
    context.moveTo(50, 0);
    context.lineTo(110, 180);
    context.lineTo(90, 180);
    context.lineTo(30, 0);
    context.fill();

    context.beginPath();
    context.moveTo(150, 0);
    context.lineTo(90, 180);
    context.lineTo(110, 180);
    context.lineTo(170, 0);
    context.fill();

    context.fillRect(150, 0, 20, 180);
}

function drawLetterA(context)
{
    context.fillStyle = "rgb(255, 0, 0)";

    context.beginPath();
    context.moveTo(220, 180);
    context.lineTo(320, 0);
    context.lineTo(340, 0);
    context.lineTo(240, 180);
    context.fill();

    context.beginPath();
    context.moveTo(420, 180);
    context.lineTo(340, 0);
    context.lineTo(320, 0);
    context.lineTo(400, 180);
    context.fill();

    context.fillRect(265, 105, 120, 15);
}

function drawLetterC(context)
{
    context.strokeStyle = "rgb(128, 0, 255)";

    const startAngle = (Math.PI / 180) * 60;
    const endAngle = (Math.PI / 180) * 300;
    
    context.beginPath();
    context.arc(540, 90, 80, startAngle, endAngle, false);
    context.lineWidth = 20;
    context.stroke();
}
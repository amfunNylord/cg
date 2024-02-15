window.onload = () => {
    const canvas = document.getElementById("canvas");
    const context = canvas.getContext("2d");

    drawNature(context);
    drawHouse(context);
    drawFence(context);

    useDragAndDrop(canvas);
}

function drawNature(context)
{
    context.fillStyle = "rgb(0, 0, 255)";
    context.fillRect(0, 0, 640, 240);

    context.fillStyle = "rgb(0, 255, 0)";
    context.fillRect(0, 240, 640, 240);
}

function drawHouse(context) 
{
    drawWall(context);
    drawRoof(context);
    drawDoor(context);
    drawWindow(context);
    drawChimney(context);
}

function drawRoof(context)
{
    context.fillStyle = "rgb(122, 79, 25)";
    context.beginPath();
    context.moveTo(0, 140);
    context.lineTo(240, 140);
    context.lineTo(120, 70);
    context.lineTo(0, 140);
    context.fill();
}

function drawWindow(context)
{
    context.fillStyle = "rgb(105, 232, 247)";
    context.fillRect(40, 200, 80, 80);

    context.strokeStyle = "rgb(13, 114, 220)";
    context.strokeRect(40, 200, 80, 80);

    context.fillStyle = "rgb(13, 114, 220)";
    context.fillRect(40, 240, 80, 2);
    context.fillRect(80, 200, 2, 80);
}

function drawDoor(context)
{
    context.beginPath();
    context.moveTo(150, 320);
    context.lineTo(200, 320);
    context.lineTo(200, 190);
    context.lineTo(150, 190);
    context.lineTo(150, 320);
    context.fill();

    context.strokeStyle = "rgb(98, 52, 19)";
    context.beginPath();
    context.arc(185, 260, 5, 0, 2 * Math.PI, false);
    context.stroke();
}

function drawChimney(context)
{
    context.fillStyle = "rgb(128, 128, 128)";
    context.beginPath();
    context.moveTo(170, 104);
    context.lineTo(200, 120);
    context.lineTo(200, 80);
    context.lineTo(170, 80);
    context.lineTo(170, 104);
    context.fill();
}

function drawWall(context)
{
    context.fillStyle = "rgb(128, 128, 128)";
    context.fillRect(20, 140, 200, 200);
}

function drawFence(context) 
{
    context.fillStyle = "rgb(240, 253, 28)";

    for (var i = 10; i < 640; i += 30)
    {
        context.fillRect(i, 300, 20, 150);
    }

    context.fillRect(0, 350, 640, 5);
    context.fillRect(0, 400, 640, 5);
}
// сделать два домика и один из них меньше 
function useDragAndDrop(element)
{
    var isDragging = false;
    var offsetX, offsetY;

    element.addEventListener("mousedown", function(e) {
        isDragging = true;
        offsetX = e.clientX - element.getBoundingClientRect().left;
        offsetY = e.clientY - element.getBoundingClientRect().top;
    });

    element.addEventListener("mouseup", function() {
        isDragging = false;
    });

    element.addEventListener("mousemove", function(e) {
        if (isDragging) {
            var x = e.clientX - offsetX;
            var y = e.clientY - offsetY;

            element.style.left = x + "px";
            element.style.top = y + "px";
        }
    });
}
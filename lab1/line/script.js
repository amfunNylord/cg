document.addEventListener('DOMContentLoaded', function () {
    const canvas = document.getElementById('canvas');
    const context = canvas.getContext('2d');

    let start = null;

    window.drawLineFromConsole = function(x1, y1, x2, y2, color) {
        drawLine({ x: x1, y: y1 }, { x: x2, y: y2 }, color);
      };

    function drawLine(start, end, color) {
      let x1 = start.x;
      let y1 = start.y;
      const x2 = end.x;
      const y2 = end.y;

      const dx = Math.abs(x2 - x1);
      const dy = Math.abs(y2 - y1);
      const sx = x1 < x2 ? 1 : -1;
      const sy = y1 < y2 ? 1 : -1;
      let err = dx - dy;

      while (true) {
        context.fillStyle = color;
        context.fillRect(x1, y1, 1, 1);

        if (x1 === x2 && y1 === y2) {
          break;
        }

        const e2 = 2 * err;

        if (e2 > -dy) {
          err -= dy;
          x1 += sx;
        }

        if (e2 < dx) {
          err += dx;
          y1 += sy;
        }
      }
    }
  });
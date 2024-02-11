document.addEventListener('DOMContentLoaded', function () {
    const canvas = document.getElementById('canvas');
    const context = canvas.getContext('2d');

    window.drawLine = function(x1, y1, x2, y2, color) {
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

    window.drawCircle = function(x1, y1, radius, color) {
        let x = 0;
        let y = radius;
        let delta = 1 - 2 * radius;
        let error = 0;
        while (y >= x)
        {
            context.fillStyle = color;
            context.fillRect(x1 + x, y1 + y, 1, 1);
            context.fillRect(x1 + x, y1 - y, 1, 1);
            context.fillRect(x1 - x, y1 + y, 1, 1);
            context.fillRect(x1 - x, y1 - y, 1, 1);
            context.fillRect(x1 + y, y1 + x, 1, 1);
            context.fillRect(x1 + y, y1 - x, 1, 1);
            context.fillRect(x1 - y, y1 + x, 1, 1);
            context.fillRect(x1 - y, y1 - x, 1, 1);
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0))
            {
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0))
            {
                delta -= 2 * --y + 1;
                continue;
            }
            delta += 2 * (++x - --y);
        }
}
});
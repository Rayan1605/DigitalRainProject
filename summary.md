Console Render is basically decide what colours and it places the letters on the screen, 
but it grabs them from getRandomChar() in RainDrop.h/.cpp. 
It doesn’t “decide” what they are—it just paints what RainDrop hands over.

The raindrop > This handle where the letters are placed
shifts the yPositions down, making that falling effect happen.


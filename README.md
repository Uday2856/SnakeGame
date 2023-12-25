A snakes game is a classic arcade game where the player controls a snake that moves around the screen, eating food and avoiding obstacles.
The snake grows longer as it eats food, and the game ends if the snake hits the edge of the screen or its own body.

To implement a snakes game using arrays, we need to use the following data structures:

1. A two-dimensional array of integers to represent the board. Each cell of the board can have one of the following values: 0 for empty, 1 for food, 2 for snake head, and 3 for snake body.
2. A one-dimensional array of integers to store the direction of the snake. The direction can be one of the following values: 0 for up, 1 for right, 2 for down, and 3 for left.
3. A one-dimensional array of integers to store the coordinates of the snake’s body. The coordinates are stored as pairs of row and column indices, starting from the head and ending at the tail.

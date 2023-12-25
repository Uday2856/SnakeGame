#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the size of the board
#define ROWS 10
#define COLS 10

// Define the values for the board cells
#define EMPTY 0
#define FOOD 1
#define HEAD 2
#define BODY 3

// Define the values for the direction
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// Define the maximum length of the snake
#define MAX_LENGTH 20

// Declare the global variables
int board[ROWS][COLS]; // The board array
int direction; // The direction of the snake
int snake[MAX_LENGTH * 2]; // The snake array
int length; // The length of the snake
int score; // The score of the game
int game_over; // The flag for game over

// Initialize the game
void init_game() {
  // Initialize the random seed
  srand(time(NULL));

  // Initialize the board with empty cells
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = EMPTY;
    }
  }

  // Initialize the snake with one cell at the center of the board
  int row = ROWS / 2;
  int col = COLS / 2;
  board[row][col] = HEAD;
  snake[0] = row;
  snake[1] = col;
  length = 1;

  // Initialize the direction to right
  direction = RIGHT;

  // Initialize the score to zero
  score = 0;

  // Initialize the game over flag to false
  game_over = 0;

  // Generate the first food
  generate_food();
}

// Generate a food at a random empty cell
void generate_food() {
  // Find all the empty cells
  int empty_cells[ROWS * COLS][2];
  int count = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board[i][j] == EMPTY) {
        empty_cells[count][0] = i;
        empty_cells[count][1] = j;
        count++;
      }
    }
  }

  // Choose a random empty cell
  int index = rand() % count;
  int row = empty_cells[index][0];
  int col = empty_cells[index][1];

  // Place the food on the board
  board[row][col] = FOOD;
}

// Move the snake in the current direction
void move_snake() {
  // Get the current head position
  int head_row = snake[0];
  int head_col = snake[1];

  // Calculate the next head position based on the direction
  int next_row = head_row;
  int next_col = head_col;
  switch (direction) {
    case UP:
      next_row--;
      break;
    case RIGHT:
      next_col++;
      break;
    case DOWN:
      next_row++;
      break;
    case LEFT:
      next_col--;
      break;
  }

  // Check if the next head position is valid
  if (next_row < 0 || next_row >= ROWS || next_col < 0 || next_col >= COLS) {
    // The snake hits the edge of the board, game over
    game_over = 1;
    return;
  }

  if (board[next_row][next_col] == BODY) {
    // The snake hits its own body, game over
    game_over = 1;
    return;
  }

  // The next head position is valid, move the snake
  if (board[next_row][next_col] == FOOD) {
    // The snake eats the food, grow the snake and generate a new food
    length++;
    score++;
    generate_food();
  } else {
    // The snake does not eat the food, remove the tail
    int tail_row = snake[length * 2 - 2];
    int tail_col = snake[length * 2 - 1];
    board[tail_row][tail_col] = EMPTY;
  }

  // Shift the snake array to make room for the new head
  for (int i = length * 2 - 1; i > 1; i--) {
    snake[i] = snake[i - 2];
  }

  // Add the new head to the snake array
  snake[0] = next_row;
  snake[1] = next_col;

  // Update the board with the new head
  board[next_row][next_col] = HEAD;
}

// Change the direction of the snake
void change_direction(int new_direction) {
  // Check if the new direction is valid
  if (abs(new_direction - direction) != 2) {
    // The new direction is not opposite to the current direction, update the direction
    direction = new_direction;
  }
}

// Display the board and the score
void display_game() {
  // Clear the screen
  system("cls");

  // Print the board
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      switch (board[i][j]) {
        case EMPTY:
          printf(" ");
          break;
        case FOOD:
          printf("*");
          break;
        case HEAD:
          printf("@");
          break;
        case BODY:
          printf("#");
          break;
      }
    }
    printf("\n");
  }

  // Print the score
  printf("Score: %d\n", score);
}

// Get the user input
void get_input() {
  // Check if any key is pressed
  if (kbhit()) {
    // Get the key code
    int key = getch();

    // Change the direction based on the key code
    switch (key) {
      case 72: // Up arrow key
        change_direction(UP);
        break;
      case 77: // Right arrow key
        change_direction(RIGHT);
        break;
      case 80: // Down arrow key
        change_direction(DOWN);
        break;
      case 75: // Left arrow key
        change_direction(LEFT);
        break;
    }
  }
}

// The main function
int main() {
  // Initialize the game
  init_game();

  // Start the game loop
  while (!game_over) {
    // Move the snake
    move_snake();

    // Display the game
    display_game();

    // Get the user input
    get_input();

    // Wait for some time
    Sleep(100);
  }

  // Game over, print a message
  printf("Game over!\n");

  // Exit the program
  return 0;
}

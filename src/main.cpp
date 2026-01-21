#include <iostream>
using namespace std;

const int SCREEN_HEIGHT = 40;
const int SCREEN_WIDTH = 80;

// Scene buffer - represents what will be drawn to screen
char scene[SCREEN_HEIGHT][SCREEN_WIDTH];

// Initialize the scene buffer with empty spaces
void init_scene() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            scene[i][j] = ' ';
        }
    }
}

void clear_screen() {
    // ANSI escape code to clear screen and move cursor to top-left
    cout << "\033[2J\033[1;1H";
}

// Draw a single character at position (row, col)
void draw_char(int row, int col, char c) {
    if (row >= 0 && row < SCREEN_HEIGHT && col >= 0 && col < SCREEN_WIDTH) {
        scene[row][col] = c;
    }
}

// Draw the stickman at a specific position
void draw_stickman(int start_row, int start_col) {
    // Head
    draw_char(start_row, start_col, 'O');
    
    // Body
    draw_char(start_row + 1, start_col, '|');
    draw_char(start_row + 2, start_col, '|');
    
    // Arms
    draw_char(start_row + 1, start_col - 1, '/');
    draw_char(start_row + 1, start_col + 1, '\\');
    
    // Legs
    draw_char(start_row + 3, start_col - 1, '/');
    draw_char(start_row + 3, start_col + 1, '\\');
}

// Render the entire scene buffer to the screen
void render_scene() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            cout << scene[i][j];
        }
        cout << '\n';
    }
}

// Main draw function - clears and redraws everything
void draw_scene() {
    // Clear the scene buffer
    init_scene();
    
    // Draw the stickman in the middle of the screen
    draw_stickman(10, 40);
    
    // You can add more objects here later
    // Example: draw_stickman(15, 20);
    
    // Render to screen
    clear_screen();
    render_scene();
}

int main() {
  // Initial draw
  // draw_scene();
  init_scene();
  int y = 10;
  int x = 40;
  char key_pressed = ' ';
  
  // Keep redrawing until user presses Enter
  while (key_pressed != 'q') {
    init_scene();
    draw_stickman(y,x);
    clear_screen();
    render_scene();
    key_pressed = getchar();
    switch (key_pressed) {
      case 'w':
        y -= 1;
        break;
      case 's':
        y += 1;
        break;
      case 'a':
        x -= 1;
        break;
      case 'd':
        x += 1;
        break;
      default:
        break;
    }
  }
  
  cout << "Program ended.\n";
  return 0;
}

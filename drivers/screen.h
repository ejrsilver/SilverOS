#ifndef SCREEN_H
#define SCREEN_H

#define VGA_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define BLACK   0x0
#define BLUE    0x1
#define GREEN   0x2
#define CYAN    0x3
#define RED     0x4
#define MAGENTA 0x5
#define BROWN   0x6
#define GRAY    0x7
#define WHITE   0xf

#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void print_string_at(char *message, int col, int row, char attr);
void print_string(char *message, char attr);

#endif
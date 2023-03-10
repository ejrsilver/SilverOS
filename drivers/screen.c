#include "ports.h"
#include "screen.h"
#include "../kernel/util.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void print_string_at(char* message, int row, int col, char attr) {
  int offset;
  if (col >0 && row > 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
  
  int i = 0;
  while (message[i] != 0) {
    offset = print_char(message[i++], col, row, attr);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void print_string(char* message, char attr) {
  print_string_at(message,-1,-1, attr);
}

void kprint_at(char* message, int row, int col) {
  print_string_at(message, row, col, WHITE_ON_BLACK);
}

void kprint(char* message) {
  print_string_at(message,-1,-1, WHITE_ON_BLACK);
}

int print_char(char c, int col, int row, char attr) {
  unsigned char *vidmem = (unsigned char*) VGA_ADDRESS;
  if (!attr) {
    attr = WHITE_ON_BLACK;
  }
  
  if (col >= MAX_COLS || row >= MAX_ROWS) {
    vidmem[2*MAX_COLS*MAX_ROWS-2] = 'E';
    vidmem[2*MAX_COLS*MAX_ROWS-1] = RED_ON_WHITE;
    return -1;
  }
  
  int offset;
  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }
  
  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row+1);
  } else {
    vidmem[offset] = c;
    vidmem[offset+1] = attr;
    offset += 2;
  }
  
  if (offset >=MAX_COLS * MAX_ROWS * 2) {
    int i;
    for(i = 1; i < MAX_ROWS; i++) {
      memory_copy((char*) (get_offset(0, i) + VGA_ADDRESS),
                  (char*) (get_offset(0, i-1) + VGA_ADDRESS),
                  MAX_COLS * 2);
    }
    char* last_line = (char*) (get_offset(0, MAX_ROWS-1) + VGA_ADDRESS);
    for (i = 0; i < MAX_COLS * 2; i++) {
      last_line[i] = 0;
    }
      offset -= 2 * MAX_COLS;
  }
  
  set_cursor_offset(offset);
  return offset;
}

int get_cursor_offset() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  int pos = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  pos += port_byte_in(REG_SCREEN_DATA);
  int offset = pos*2;
  return offset;
}

void set_cursor_offset(int offset) {
  offset/=2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  int i;
  char *vga = (char*) VGA_ADDRESS;
  
  for(i = 0; i < screen_size; i++) {
    vga[i*2] = ' ';
    vga[i*2+1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(0);
}

int get_offset(int col, int row) {
  return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) {
  return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset) {
  return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}

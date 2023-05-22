#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../kernel/util.h"
#include "../cpu/types.h"

void init_keyboard();
void print_letter(u8 scancode);

#endif
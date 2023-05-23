#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main() {
  clear_screen();
  isr_install();

  __asm__ __volatile__ ("sti");
  init_keyboard();
  init_timer(1);
}

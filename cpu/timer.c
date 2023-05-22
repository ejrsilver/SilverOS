#include "timer.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
  tick++;
  print_string("Tick: ", WHITE_ON_BLACK);
  char tick_ascii[256];
  int_to_ascii(tick, tick_ascii);
  print_string(tick_ascii, WHITE_ON_BLACK);
  print_string("\n", WHITE_ON_BLACK);
}

void init_timer(u32 freq) {
  register_interrupt_handler(IRQ0, timer_callback);
  // clock rate
  u32 divisor = 1193180 / freq;
  u8 low = (u8)  ( divisor & 0xFF );
  u8 high = (u8) ( (divisor >> 8) & 0xFF );

  port_byte_out(0x42, 0x36);
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}

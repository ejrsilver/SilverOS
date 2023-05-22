#ifndef IDT_H
#define IDT_H

#include "types.h"
#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

typedef struct {
  u16 low_offset; // Low 16-bits of handler addr.
  u16 sel; // seg select
  u8 always0; // 7: int, 6-5: privilege, 4: 0 for int gates, 3-0: bits 1110 = 14 = 'int gate'
  u8 flags;
  u16 high_offset; // high bits
} __attribute__((packed)) idt_gate_t;

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_register_t;

extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
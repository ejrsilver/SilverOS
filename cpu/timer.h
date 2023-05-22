#ifndef TIMER_H
#define TIMER_H

#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../kernel/util.h"
#include "isr.h"
#include "types.h"

void init_timer(u32 freq);

#endif
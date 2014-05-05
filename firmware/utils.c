

#include <p24Fxxxx.h>

#include "pin_defs.h"
#include "globals.h"

void delay(short d) {
    short i;
    for (i = 0; i < d; i++) {
        Nop();
    }
}

void BlinkAlive(short pulse) {
    HEARTBEAT = 1;
    delay(pulse);
    HEARTBEAT = 0;
    delay(pulse);
}

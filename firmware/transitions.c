
#include <p24Fxxxx.h>

#include "pin_defs.h"
#include "display.h"
//#include "numbers.h"
#include "globals.h"
#include "utils.h"

void Intro(void) {
    short i, j, k;

    ANODE_DC = 0;
    RED_DC = 0;
    GREEN_DC = 256;


    left_ptr = &left[0];
    right_ptr = &right[0];

    leftbuf_ptr = sprites[3];
    rightbuf_ptr = sprites[4];
    //leftbuf_ptr = &filled[3];
    //rightbuf_ptr = &filled[0];

    while (right_ptr < &right[8]) {
        for (i = 0; i < 8; i++) {
            *left_ptr = *leftbuf_ptr;
            left_ptr++;
            leftbuf_ptr++;
            *right_ptr = *rightbuf_ptr;
            right_ptr++;
            rightbuf_ptr++;
        }
    }

    for (j = 0; j < 30; j++) {
        for (k = 0; k < 10; k++) {

            left_ptr = &left[7];
            right_ptr = &right[7];
            anode_ptr = &anode[7];

            display();
            delay(550);


            if (dir) {
                ANODE_DC = ANODE_DC + offset;
                if (ANODE_DC >= 250) {
                    dir = 0;
                }
            } else {
                ANODE_DC = ANODE_DC - offset;
                if (ANODE_DC <= 5) {
                    dir = 1;
                }
            }
        }
        RED_DC++;
        GREEN_DC--;
    }

    dir = 1;
    RED_DC = 0;
    GREEN_DC = 0;
    ANODE_DC = 0;
}

void transition_fall(void) {

}

void transition_crossfade(void) {
    for (globi = 0; globi < (fadelevels - fadepos); globi++) {

        left_ptr = &left[7];
        right_ptr = &right[7];
        anode_ptr = &anode[7];

        display();
    }

    for (globi = 0; globi < fadepos; globi++) {
        left_ptr = &leftbuf[7];
        right_ptr = &rightbuf[7];
        anode_ptr = &anode[7];

        display();
    }

    if (crossratebuf <= 0) {
        fadepos++;
        crossratebuf = crossrate;
    } else {
        crossratebuf--;
    }
}

void transition_fadein(void) {
    while (ANODE_DC > (0 + faderate)) {
        ANODE_DC = ANODE_DC - faderate;

        left_ptr = &left[7];
        right_ptr = &right[7];
        anode_ptr = &anode[7];

        display();
    }

    ANODE_DC = 0;
}

void transition_fadeout(void) {
    while (ANODE_DC < (PERIOD - faderate)) {
        ANODE_DC = ANODE_DC + faderate;

        left_ptr = &left[7];
        right_ptr = &right[7];
        anode_ptr = &anode[7];

        display();
    }

    ANODE_DC = PERIOD;
}

void transition_crossdissolve(void) {
    transition_fadeout();
    unload_buffer();
    transition_fadein();
}

void rotate_left(void) {
    left_ptr = &left[7];
    right_ptr = &right[7];

    unsigned char row_left[8] = {0};
    unsigned char row_right[8] = {0};
    int loop = 0;
    for (loop = 0; loop < 8; loop++) {
        leftbuf_ptr = &leftbuf[0];
        rightbuf_ptr = &rightbuf[0];

        for (globi = 0; globi < 8; globi++) {
            row_left[globi] = (*left_ptr >> globi) & 0x01;
            row_right[globi] = (*right_ptr >> globi) & 0x01;
        }

        for (globi = 0; globi < 8; globi++) {
            *leftbuf_ptr = ((*leftbuf_ptr) << 1) | row_left[globi];
            *rightbuf_ptr = ((*rightbuf_ptr) << 1) | row_right[globi];

            leftbuf_ptr++;
            rightbuf_ptr++;
        }

        left_ptr--;
        right_ptr--;
    }

    unload_buffer();
}

void rotate_180(void) {
    leftbuf_ptr = &leftbuf[7];
    rightbuf_ptr = &rightbuf[7];

    left_ptr = &left[0];
    right_ptr = &right[0];

    while (right_ptr < &right[7]) {
        for (globi = 0; globi < 8; globi++) {
            *leftbuf_ptr = *left_ptr;
            *rightbuf_ptr = *right_ptr;

            leftbuf_ptr--;
            rightbuf_ptr--;

            left_ptr++;
            right_ptr++;
        }
    }

    unload_buffer();
}



#include <p24Fxxxx.h>
#include <stdlib.h>
#include <math.h>

#include "pin_defs.h"
#include "display.h"
#include "globals.h"
#include "utils.h"

#include "numbers.h"
#include "faces.h"
#include "sprites.h"
#include "letters.h"

unsigned long dots[24] ={
    0b11111111111111111111111111111111,
    0b11111111111111111111111111111111,
    0b11111101111111111111111111111111,
    0b10101101111111111111111111111111,
    0b01010111111111111111111111111111,
    0b01010101111111111111111111111111,
    0b01110101111111111111111111111111,
    0b01110101111111111111111111111111, //8

    0b11111111111111111111111111111111,
    0b11111111111111111111111111111111,
    0b11111101111111111111111111111111,
    0b10101101111111111111111111111111,
    0b01010111111111111111111111111111,
    0b01010101111111111111111111111111,
    0b01110101111111111111111111111111,
    0b01110101111111111111111111111111, //16

    0b11111111111111111111111111111111,
    0b11111111111111111111111111111111,
    0b11111101111111111111111111111111,
    0b10101101111111111111111111111111,
    0b01010111111111111111111111111111,
    0b01010101111111111111111111111111,
    0b01110101111111111111111111111111,
    0b01110101111111111111111111111111 //24
};

unsigned char *left_ptr;
unsigned char left[8] ={
    0b11111111,
    0b11111111,
    0b11111101,
    0b10101101,
    0b01010111,
    0b01010101,
    0b01110101,
    0b01110101
};

unsigned char *leftbuf_ptr;
unsigned char leftbuf[8] ={
    0b11111111,
    0b11110111,
    0b11110111,
    0b10010101,
    0b01110111,
    0b10110101,
    0b11010101,
    0b00010100
};

unsigned char *right_ptr;
unsigned char right[8] ={
    0b11111111,
    0b11111111,
    0b11111111,
    0b10111001,
    0b01010101,
    0b01110011,
    0b01010110,
    0b10111001
};

unsigned char *rightbuf_ptr;
unsigned char rightbuf[8] ={
    0b11111111,
    0b11011111,
    0b11011111,
    0b11011001,
    0b10110101,
    0b01010011,
    0b01010110,
    0b10111001
};

unsigned char *anode_ptr;
unsigned char anode[8] ={
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000
};

unsigned char *anodebuf_ptr;
unsigned char anodebuf[8] ={
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

void display(void) {
    char red_rand;
    char green_rand;

    while (anode_ptr >= &anode[0]) {
        short i, loop;

        unsigned char hour_data;
        unsigned char minute_data;
        unsigned char rotate = 0xfe;
        unsigned char rotatebuf = 0x00;
        unsigned int randR = 0;
        unsigned int randG = 0;

        for (i = 0; i < 8; i++) {
            hour_data = *left_ptr | (rotate);
            minute_data = *right_ptr | (rotate);
            __asm__ volatile ("rlnc.b %0, %1" : "=r"(rotatebuf) : "r"(rotate));
            rotate = rotatebuf;

            MCLR = 1;
            delay(d);

            STORE = 0;
            delay(d);

            for (loop = 0; loop < 8; loop++) {
                CLK_LEFT_RED = 0;
                delay(1);
                CLK_LEFT_GREEN = 0;
                delay(1);
                DATA = (hour_data >> loop) & 0x01;
                delay(d);
                CLK_LEFT_RED = 1;
                delay(1);
                CLK_LEFT_GREEN = 1;
                delay(1);

                CLK_RIGHT_RED = 0;
                delay(1);
                CLK_RIGHT_GREEN = 0;
                delay(1);
                DATA = (minute_data >> loop) & 0x01;
                delay(d);
                CLK_RIGHT_RED = 1;
                delay(1);
                CLK_RIGHT_GREEN = 1;
                delay(1);

                CLK_ANODE = 0;
                delay(1);
                DATA = (*anode_ptr >> loop) & 0x01;
                delay(d);
                CLK_ANODE = 1;
                delay(1);
            }

            STORE = 1;
            delay(d);

            MCLR = 0;
            delay(d);

            if (model == monk_1 || model == belt_1) {
                randR = rand() / (int) (((unsigned) RAND_MAX + 1) / 255);
                randG = rand() / (int) (((unsigned) RAND_MAX + 1) / 255);

                //srand(seconds_ones);
                red_rand = randR;
                RED_DC = red_rand;
                green_rand = randG;
                GREEN_DC = green_rand;
            }
        }

        left_ptr--;
        right_ptr--;
        anode_ptr--;
    }
}

void update_number() {
    if (model == clock_1 || model == clock_2 || model == clock_3) {
        RCFGCALbits.RTCPTR = 0b01; // set pointer to read weekday/hours
        hours = (RTCVAL & 0x007F);
        hours_tens = (hours & 0x0070) >> 4;
        hours_ones = (hours & 0x000F);
        RCFGCALbits.RTCPTR = 0b00; // set pointer to read minutes/seconds (remains here)
        minutes = (RTCVAL & 0x7F00) >> 8;
        minutes_tens = (minutes & 0x0070) >> 4;
        minutes_ones = (minutes & 0x000F);
        seconds = (RTCVAL & 0x007F);
        seconds_tens = (seconds & 0x0070) >> 4;
        seconds_ones = seconds & 0x000F;
    } else {
        minutes = countVarLeft % 100;
        minutes_tens = (minutes / 10);
        minutes_ones = (minutes % 10);

        seconds = countVarRight % 100;
        seconds_tens = (seconds / 10);
        seconds_ones = (seconds % 10);
    }



    if (model == clock_1 || model == clock_2 || model == clock_3) {
        if (hours == 0x0000) {
            hours_tens = 1;
            hours_ones = 2;
        } else if (hours > 0x0012) {
            hours_tens = hours_tens - 1;
            hours_ones = hours_ones - 2;
        }

        if (seconds == 0x0000) {
            if ((hours == 0x0000) && (minutes == 0x0000)) {
                RED_DC = 0;
                GREEN_DC = 0;
                ANODE_DC = 0;
            } else if (hours >= 0x0000 && hours < 0x0006) {
                RED_DC++;
            } else if (hours >= 0x0006 && hours < 0x0012) {
                RED_DC--;
            } else if (hours >= 0x0012 && hours < 0x0018) {
                GREEN_DC++;
            } else if (hours >= 0x0018 && hours <= 0x0024) {
                GREEN_DC--;
            }
        }
    } else {


    }



    if (hours == minutes && minutes == seconds) {
        left_ptr = sprites[1];
        right_ptr = sprites[0];
    } else {

        left_ptr = &left[0];
        right_ptr = &right[0];

#ifdef showsec
        left_tens_ptr = numbers[minutes_tens][0];
        left_ones_ptr = numbers[minutes_ones][0];
        right_tens_ptr = numbers[seconds_tens][0];
        right_ones_ptr = numbers[seconds_ones][0];
#ifdef showsec_bkwrd
        right_tens_ptr = numbers[minutes_tens][0];
        right_ones_ptr = numbers[minutes_ones][0];
        left_tens_ptr = numbers[seconds_tens][0];
        left_ones_ptr = numbers[seconds_ones][0];
#endif
#else
        left_tens_ptr = numbers[hours_tens];
        left_ones_ptr = numbers[hours_ones];
        right_tens_ptr = numbers[minutes_tens];
        right_ones_ptr = numbers[minutes_ones];
#endif

    }

    while (right_ptr < &right[8]) {
        short left_temp = 0xff;
        left_temp = left_temp & (*left_tens_ptr << 5);
        left_temp = left_temp | *left_ones_ptr;
        left_temp = left_temp | 0b00011000;
        *left_ptr = left_temp;

        left_tens_ptr++;
        left_ones_ptr++;
        left_ptr++;


        short right_temp = 0xff;
        right_temp = right_temp & (*right_tens_ptr << 5);
        right_temp = right_temp | *right_ones_ptr;
        right_temp = right_temp | 0b00011000;
        *right_ptr = right_temp;

        right_tens_ptr++;
        right_ones_ptr++;
        right_ptr++;
    }

    Nop();
}

void load_buffer(void) {
    leftbuf_ptr = &leftbuf[0];
    rightbuf_ptr = &rightbuf[0];

    while (rightbuf_ptr < &rightbuf[7]) {
        for (globi = 0; globi < 8; globi++) {
            *leftbuf_ptr = *faceOne_ptr;
            *rightbuf_ptr = *faceTwo_ptr;
            leftbuf_ptr++;
            rightbuf_ptr++;
            faceOne_ptr++;
            faceTwo_ptr++;
        }
    }
}

void unload_buffer(void) {
    leftbuf_ptr = &leftbuf[0];
    rightbuf_ptr = &rightbuf[0];

    left_ptr = &left[0];
    right_ptr = &right[0];

    while (right_ptr < &right[7]) {
        for (globi = 0; globi < 8; globi++) {
            *left_ptr = *leftbuf_ptr;
            *right_ptr = *rightbuf_ptr;

            leftbuf_ptr++;
            rightbuf_ptr++;

            left_ptr++;
            right_ptr++;
        }
    }
}

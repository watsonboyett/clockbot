

#ifndef SPRITES_H
#define	SPRITES_H


const unsigned char pac_ghost[8] ={
    0b11111111,
    0b11000011,
    0b10111101,
    0b01011010,
    0b01011010,
    0b01111110,
    0b01011010,
    0b00100100,
};

const unsigned char pac_open[8] ={
    0b11100011,
    0b11011101,
    0b10111011,
    0b01110110,
    0b01110110,
    0b10111011,
    0b11011101,
    0b11100011,
};

const unsigned char pac_ghost2[8] ={
    0b11111111,
    0b11000011,
    0b10111101,
    0b01011010,
    0b01011010,
    0b01111110,
    0b00100100,
    0b01011010,
};

const unsigned char heart[8] ={
    0b11111111,
    0b10011001,
    0b01100110,
    0b01111110,
    0b01111110,
    0b10111101,
    0b11011011,
    0b11100111,
};

const unsigned char null[8] ={
    0b11111110,
    0b11000101,
    0b10111001,
    0b01110110,
    0b01101110,
    0b10011101,
    0b10100011,
    0b01111111,
};

const unsigned char horny[8] ={
    0b10111101,
    0b01111110,
    0b10100101,
    0b11011011,
    0b10111101,
    0b10111101,
    0b01111110,
    0b01111110,
};

const unsigned char maze[8] ={
    0b01000000,
    0b01011110,
    0b01010010,
    0b01001010,
    0b01011010,
    0b01000010,
    0b01111110,
    0b00000000,
};

const unsigned char *sprites[7] ={
    pac_open, pac_ghost, pac_ghost2, heart, null, horny, maze
};

/*---------------------------------------------------------------------------*/

const unsigned char hourglass[4][8] ={
    {
        0b10000001,
        0b10111101,
        0b11011011,
        0b11100111,
        0b11100111,
        0b11011011,
        0b10111101,
        0b10000001,
    },

    {
        0b11100111,
        0b11101011,
        0b11101101,
        0b00001110,
        0b01110000,
        0b10110111,
        0b11010111,
        0b11100111,
    },

    {
        0b11111111,
        0b00111100,
        0b01011010,
        0b01100110,
        0b01100110,
        0b01011010,
        0b00111100,
        0b11111111,
    },

    {
        0b11100111,
        0b11010111,
        0b10110111,
        0b01110000,
        0b00001110,
        0b11101101,
        0b11101011,
        0b11100111,
    },
};

const unsigned char dash_open[8][8] ={
    {
        0b01111111,
        0b10111111,
        0b11011111,
        0b11101111,
        0b11110111,
        0b11111011,
        0b11111101,
        0b11111110,
    },

    {
        0b10111111,
        0b01011111,
        0b10101111,
        0b11010111,
        0b11101011,
        0b11110101,
        0b11111010,
        0b11111101,
    },

    {
        0b11011111,
        0b10101111,
        0b01110111,
        0b10111011,
        0b11011101,
        0b11101110,
        0b11110101,
        0b11111011,
    },

    {
        0b11101111,
        0b11010111,
        0b10111011,
        0b01111101,
        0b10111110,
        0b11011101,
        0b11101011,
        0b11110111,
    },

    {
        0b11110111,
        0b11101011,
        0b11011101,
        0b10111110,
        0b01111101,
        0b10111011,
        0b11010111,
        0b11101111,
    },

    {
        0b11111011,
        0b11110101,
        0b11101110,
        0b11011101,
        0b10111011,
        0b01110111,
        0b10101111,
        0b11011111,
    },

    {
        0b11111101,
        0b11111010,
        0b11110101,
        0b11101011,
        0b11010111,
        0b10101111,
        0b01011111,
        0b10111111,
    },

    {
        0b11111110,
        0b11111101,
        0b11111011,
        0b11110111,
        0b11101111,
        0b11011111,
        0b10111111,
        0b01111111,
    },
};

const unsigned char spinner[14][8] ={
    {
        0b11111110,
        0b11111101,
        0b11111011,
        0b11110111,
        0b11101111,
        0b11011111,
        0b10111111,
        0b01111111,
    },

    {
        0b11111111,
        0b11111100,
        0b11111011,
        0b11110111,
        0b11101111,
        0b11011111,
        0b00111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111110,
        0b11111101,
        0b11110011,
        0b11001111,
        0b10111111,
        0b01111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b11111100,
        0b11110011,
        0b11001111,
        0b00111111,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b11111110,
        0b11110001,
        0b10001111,
        0b01111111,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11110000,
        0b00001111,
        0b11111111,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b11111111,
        0b01110001,
        0b10001110,
        0b11111111,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b11111111,
        0b00110011,
        0b11001100,
        0b11111111,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b01111111,
        0b10010111,
        0b11101001,
        0b11111110,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b11111111,
        0b00111111,
        0b11001111,
        0b11110011,
        0b11111100,
        0b11111111,
        0b11111111,
    },

    {
        0b11111111,
        0b01111111,
        0b10111111,
        0b11001111,
        0b11110011,
        0b11111101,
        0b11111110,
        0b11111111,
    },

    {
        0b11111111,
        0b01111111,
        0b10011111,
        0b11101111,
        0b11110111,
        0b11111001,
        0b11111110,
        0b11111111,
    },

    {
        0b11111111,
        0b00111111,
        0b11011111,
        0b11101111,
        0b11110111,
        0b11111011,
        0b11111100,
        0b11111111,
    },

    {
        0b01111111,
        0b10111111,
        0b11011111,
        0b11101111,
        0b11110111,
        0b11111011,
        0b11111101,
        0b11111110,
    },
};


#endif	/* SPRITES_H */

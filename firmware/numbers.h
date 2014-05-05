

#ifndef __NUMBERS_H
#define __NUMBERS_H


const unsigned char *faceOne_ptr;
const unsigned char *faceTwo_ptr;
unsigned char face = 0;


const unsigned char blank[8] ={
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
};

const unsigned char full[8] ={
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

const unsigned char checker[8] ={
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
};



/*---------------------------------------------------------------------------*/

const unsigned char *left_tens_ptr;
const unsigned char *left_ones_ptr;
const unsigned char *right_tens_ptr;
const unsigned char *right_ones_ptr;

/*---------------------------------------------------------------------------*/



//0 - led on, 1 - led off

const unsigned char zero[8] ={//0
    0b101,
    0b010,
    0b010,
    0b010,
    0b010,
    0b010,
    0b010,
    0b101
};

const unsigned char one[8] ={//1
    0b101,
    0b001,
    0b101,
    0b101,
    0b101,
    0b101,
    0b101,
    0b101
};

const unsigned char two[8] ={//2
    0b001,
    0b110,
    0b110,
    0b101,
    0b011,
    0b011,
    0b011,
    0b100
};

const unsigned char three[8] ={//3
    0b001,
    0b110,
    0b110,
    0b001,
    0b110,
    0b110,
    0b110,
    0b001
};

const unsigned char four[8] ={//4
    0b010,
    0b010,
    0b010,
    0b101,
    0b110,
    0b110,
    0b110,
    0b110
};

const unsigned char five[8] ={//5
    0b100,
    0b011,
    0b011,
    0b101,
    0b110,
    0b110,
    0b110,
    0b001
};

const unsigned char six[8] ={//6
    0b100,
    0b011,
    0b011,
    0b101,
    0b010,
    0b010,
    0b010,
    0b101
};

const unsigned char seven[8] ={//7
    0b001,
    0b110,
    0b110,
    0b101,
    0b101,
    0b101,
    0b101,
    0b101,
};

const unsigned char eight[8] ={//8
    0b101,
    0b010,
    0b010,
    0b101,
    0b010,
    0b010,
    0b010,
    0b101
};

const unsigned char nine[8] ={//9
    0b101,
    0b010,
    0b010,
    0b101,
    0b110,
    0b110,
    0b110,
    0b110
};

const unsigned char ex[8] ={//X
    0b010,
    0b010,
    0b010,
    0b101,
    0b010,
    0b010,
    0b010,
    0b010
};

const unsigned char *numbers[11] ={
    zero, one, two, three, four, five, six, seven, eight, nine, ex
};

/*---------------------------------------------------------------------------*/


#endif	/* __NUMBERS_H__ */

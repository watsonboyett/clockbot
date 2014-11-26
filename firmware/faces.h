

#ifndef FACES_H
#define	FACES_H


const unsigned char game_face[8] ={
    0b11111111,
    0b11111111,
    0b11011011,
    0b11111111,
    0b11111111,
    0b10000001,
    0b11111111,
    0b11111111
};

const unsigned char smile_face[8] ={
    0b11111111,
    0b11011011,
    0b11011011,
    0b11111111,
    0b11111111,
    0b10111101,
    0b11000011,
    0b11111111
};

const unsigned char sad_face[8] ={
    0b11111111,
    0b11111111,
    0b11011011,
    0b11111111,
    0b11111111,
    0b11000011,
    0b10111101,
    0b11111111
};

const unsigned char tongue_face[8] ={
    0b11111111,
    0b11011011,
    0b11011011,
    0b11111111,
    0b11111111,
    0b10000001,
    0b11101011,
    0b11110111
};

const unsigned char open_face[8] ={
    0b11111111,
    0b11011011,
    0b11111111,
    0b11111111,
    0b11000011,
    0b10111101,
    0b11000011,
    0b11111111
};

const unsigned char exeue_face[8] ={
    0b11111111,
    0b11011011,
    0b11111111,
    0b11111111,
    0b11011011,
    0b11100111,
    0b11011011,
    0b11111111
};

const unsigned char wink_face[8] ={
    0b11111111,
    0b11011111,
    0b11010001,
    0b11111111,
    0b11111111,
    0b10111101,
    0b11000011,
    0b11111111
};

const unsigned char laugh_face[8] ={
    0b11111111,
    0b11011011,
    0b11011011,
    0b11111111,
    0b10000001,
    0b10111101,
    0b11000011,
    0b11111111
};

const unsigned char slant_face[8] ={
    0b11111111,
    0b11011011,
    0b11111111,
    0b11111111,
    0b10111111,
    0b11000011,
    0b11111101,
    0b11111111
};

const unsigned char mad_face[8] ={
    0b11111111,
    0b10111101,
    0b11011011,
    0b11111111,
    0b11111111,
    0b11000011,
    0b10011001,
    0b11111111
};

const unsigned char *faces[10] ={
    game_face, smile_face, sad_face, tongue_face, open_face, exeue_face,
    wink_face, laugh_face, slant_face, mad_face
};

#endif	/* FACES_H */
